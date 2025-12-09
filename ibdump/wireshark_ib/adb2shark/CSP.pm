#!/opt/bin/perl -w

package CSP;

# Parser of CSP files
# TODO: add formatting option
# 
# parses the Configuration space database and emits.
# as a perl structure (defined below)
#
# DATA STRUCTURE:
#
#       * all sizes are in bits.
#
#       my $node = {
#               nname  => "IB_config",
#               nsize  => 0x10000,
#               descr  => "InfiniBand Configuration Data Structure",
#               fields => [{}, {}, ...],        # see below the description of fields
#               comment_before = "#cscdsdc \n#dvdfv"
#               attr   => "attr_xxx";
#               flag  => 1 || undef             # flag for traversals
#       }
#
#       my $field = {
#               fname => "SWITCHC",
#               fsize => 0x10,
#               descr => "Switch Configuration Data Structure",
#               array    => {low_bound => 0, high_bound => 7, esize => element size} ||
#                             undef;                    # if not array
#
#               subnode  => $node ||                    # see above
#                             undef                     # if leaf
#               attr     => "attr_yyy",
#               reserved => 1 || undef
#       }
#
#       my $csp = {
#       
#               node_list =>     [$node1, $node2, ...]     # according original
#                                                          # order in file
#               node_by_name =>  { "nodename1" => $node1, ...}
#               main_node => $node,
#               C_header  => "#defiene ....\n#define ....\n ....";
#               C_header_comment => "# Copyright";
#
#       }

use strict;
use Carp;

my $convert_names;

sub new
{
    my $class    = shift;
    my $filename = shift || croak("Usage new CSP \"filename.csp\"");
    $convert_names = shift;

    my $csp;

    open (CSPFILE, "<$filename") || croak(" cannot open \"$filename\" for read");
    my @parts  = split /^=cut/m, join("", <CSPFILE>);
    close CSPFILE;

    foreach my $part (@parts)
    {
            my @part_lines          = split /\n/, $part;
            my $comment_before      = "";




            while( @part_lines && $part_lines[0] !~ /^\s*\w+/ ) {
                $comment_before .= shift(@part_lines) . "\n";
            }

            last unless @part_lines;


            if ($part_lines[0] =~ /CHEADER_RAW_DATA/) {
                    shift @part_lines;
                    $csp->{C_header} = join("\n", @part_lines);
                    $csp->{C_header_comment} = $comment_before;
                    next;
            }

            my $node =  parse_node(@part_lines);
            $node->{comment_before} = $comment_before;
            push @{$csp->{node_list}}, $node;
            $csp->{node_by_name}->{$node->{nname}} = $node;
    }

    foreach my $n (@{$csp->{node_list}}) {
        foreach my $f ( @{$n->{fields}} ) {
            $f->{subnode} &&= $csp->{node_by_name}->{$f->{subnode}}; 
        }
    }

    $csp->{main_node} = $csp->{node_list}->[0];

    #fix_nodes($csp);

    return bless $csp, $class;

}

sub align_node_reserved {
    my $node = shift;
    my $nsize = $node->{nsize};  

    my $array_index = 0;
    my $foffset = 0;
    #my $newfields = [];

    for(my $array_index =0; $array_index <= $#{$node->{fields}}; $array_index++ ) {
        #For now only fix reserved alignment
        my $f = ${$node->{fields}}[$array_index];
      
        if ($f->{reserved} and (($foffset % 32) or ($f->{fsize} % 32) ) ) {
          my @newfields = ();
          while ( int($foffset / 32) < int( ($foffset + $f->{fsize} - 1 ) /32)) {
            my $left = 32 - $foffset;
            push @newfields, ({
              fname => 'RESERVED',
              fsize => $left,
              descr => "",
              subnode => undef,
              attr => "",
              reserved => 1,
            });
            $foffset = ($foffset + $left) % 32;
            $f->{fsize} -= $left;
          }
          push @newfields, $f;
          splice @{$node->{fields}}, $array_index, 1, @newfields;
          $array_index += $#newfields;
        }
        $foffset = ($foffset + $f->{fsize}) % 32;
    }

    #$node->{fields} = $newfields;
}

sub align_reserved {
  my $csp = shift;
  foreach my $n (@{$csp->{node_list}}) {
    align_node_reserved($n);
  }
}

sub check_size {
  my $csp = shift;
  my $err=0;
  foreach my $n (@{$csp->{node_list}}) {
    my $node_size = $n->{nsize};  
    my $fields_size = 0;
    foreach my $f ( @{$n->{fields}} ) {
      if ($f->{fsize} <= 0) {
        print STDERR "ERROR: Node <" . ($n->{nname}) . "> field ", $f->{fname}, 
        " has non-positive size " , $f->{fsize}, "\n";
        $err=1;
      }
      if($f->{subnode}) {
        my $size  = $f->{array} ? $f->{array}->{esize} : $f->{fsize};
        if ($f->{subnode}->{nsize} != $size) {
          print STDERR "ERROR: Node <" . ($n->{nname}) . "> field ", $f->{fname}, 
          " has size " , $size, 
          " but has type ", $f->{subnode}->{nname}, 
          " with node size ", $f->{subnode}->{nsize}, "\n";
          $err=1;
        }
      }
      $fields_size += $f->{fsize};
    }
    if ($fields_size != $node_size) {
      print STDERR "ERROR: Node <" . ($n->{nname}) . "> has size " , $node_size, 
            " but its total fields size is ", $fields_size, "\n";
      $err=1;
    }
  }
  return $err;
}

#PAD all nodes to the proper size with reserved fields at the end 

sub pad_size {
  my $csp = shift;
  foreach my $n (@{$csp->{node_list}}) {
    my $node_size = $n->{nsize};  
    my $fields_size = 0;
    foreach my $f ( @{$n->{fields}} ) {
      $fields_size += $f->{fsize};
    }
    next if ($fields_size == $node_size);
    if ($fields_size > $node_size) {
      print STDERR "ERROR: Node <" . ($n->{nname}) . "> has size " , $node_size, 
            " but its total fields size is ", $fields_size, "\n";
    }

    my $left =  $node_size - $fields_size;

    push @{$n->{fields}}, {
        fname => 'RESERVED',
        fsize => $left,
        descr => "",
        subnode => undef,
        attr => "",
        reserved => 1,
        };
  }
}

sub dump {
    my $csp = shift;

    $csp->{C_header_comment} ||= "";
    $csp->{C_header} ||= "";

    my $out = $csp->{C_header_comment} . "CHEADER_RAW_DATA\n" .  $csp->{C_header} . "\n\n=cut\n";

    foreach my $n ( @{ $csp->{node_list} } ) {
        $out .= $n->{comment_before};
        $out .= $n->{nname} . "    " . size2str($n->{nsize});
        $out .= " " . $n->{attr} unless $n->{attr} =~ /^\s*$/;
        $out .= "    # " . $n->{descr} . "\n";

        foreach my $f ( @{$n->{fields}} ) {
            my $ftext = "    " . $f->{fname};
            if($f->{array}) {
                $ftext .= "[" . $f->{array}->{low_bound} . ".." .
                        $f->{array}->{high_bound} . "]";
                $ftext .= " " x (20 - length($ftext));
                $ftext .= " " . size2str($f->{array}->{esize});
            } else {
                $ftext .= " " x (20 - length($ftext));
                $ftext .= " " . size2str($f->{fsize});
            }

            $ftext .= " " x (28 - length($ftext));
            
            $ftext .= " node(" . $f->{subnode}->{nname} . ")" if $f->{subnode};
            $ftext .= " " . $f->{attr} unless $f->{attr} =~ /^\s*$/;
            $ftext .= " # " . $f->{descr} unless $f->{descr} =~ /^\s*$/;

            $out .= $ftext . "\n";
        }

        $out .= "=cut";
    }


    return $out;
}

sub node_by_name {
    my $csp   = shift;
    my $nname = shift;


    return $csp->{node_by_name}->{$nname};
}

sub full_name_by_offset {
    my $csp    = shift;
    my $offset = shift;  # bit offset;

    my ($name) =  find($csp->{main_node}, $offset);

    return $name;
}

sub find {
    my $node   = shift;
    my $offset = shift;

    my ($name, $field) = find_field($node, $offset);

    if ($field->{array}) {
        return ($name, $field->{array}->{esize}, $field->{descr});
    } else {
        return ($name, $field->{fsize}, $field->{descr});
    }
}

sub find_field  {
    my $node   = shift;
    my $offset = shift;

    my ($name, $size, $field);

    if ($offset >= $node->{nsize}) {
        return ("ERROR:TOO_BIG(offset=$offset >= node_size=$node->{nsize}", {fsize => $offset});
    }

    foreach my $f (@{$node->{fields}}) {
        if ($offset >= $f->{fsize}) {
            $offset = $offset - $f->{fsize};
            next;
        } else {
            $name  = $f->{fname};
            $field = $f;
            if ($f->{array}) {
                my $order = int($offset/$f->{array}->{esize});
                $name .= "[" .  ($f->{array}->{low_bound} + $order) . "]";
                $offset = $offset - $f->{array}->{esize} * $order;
                $field = $f;
            }
            if($f->{subnode}) {
                my ($fname, $fff) = find_field($f->{subnode}, $offset);
                $name .= "." . $fname;
                $field = $fff;
            } else {
                if( $offset != 0 ) {
                    $name .= "ERROR:IN_THE_MIDDLE_OF_FIELD";
                }
            }
            return ($name, $field);
        }

    }

    return ("ERROR:INTERNAL", undef);
}


sub parse_node {
    my $node_header = shift;
    my @fields      = @_;

    my ($def, $descr) = split "#", $node_header, 2;
    $descr ||= "";

    $descr =~ s/^\s+|\s+$//g;

    my @header_array = split " ", $def;
    my $nattr =undef; #Attribute not supported, must finalize format
    my $nsize = pop @header_array; # Assume size is always the last entry
    my($nname)=join('_',@header_array);
    $nname = format_node_name($nname);

    $nattr ||= "";

    my $node = {
                nname   => $nname,
                nsize   => uniform( $nsize, $nname ),
                attr    => $nattr,
                descr   => $descr,
               };

    foreach my $f (@fields) {
        next if $f =~ /^\s*$/;
        next if $f =~ /^\s*#/;
        push @{$node->{fields}}, parse_field($f);
    }

    return $node;
}

sub dummy_field {
  return  {
    fname => "UNDEFINED",
    fsize => 32,
    descr => "",
    subnode => "",
    attr => "",
    reserved => 1,
  }
}
sub parse_field {
    my $field_text = shift;

    my ($def, $descr) = split "#", $field_text, 2;
    $descr ||= "";
    $descr =~ s/^\s+|\s+$//g;

    my ($name, $size, $node, $attr);

    if ( $def =~ m/(.*)(node\s*\([^\)]*\))(.*)/ ) {
      $node=$2;
      $attr=$3; 
      ($name,$size)=split(" ", $1);
      $attr =~ s/^\s*//; 
      $attr =~ s/\s*$//; 
    } else {
      ($name, $size, $node, $attr) = split " ", $def, 4;
    }

    $node ||= "";
    $attr ||= "";

    if( $node =~ s/^node\s*\(([^\)]*)\).*$/$1/ ) {
        $node ||= $name;
        $node =~ s/\[\d+\.\.\d+\]$//;
    } else {
        $attr = "$node $attr";
        $attr =~ s/\s+/ /g;
        $attr =~ s/^\s|\s$//g;
        $node = "";
    } 

    $size = uniform( $size, $name );

    $node =~ s/^\s*//;
    $node =~ s/\s*$//;
    $node =~ s/\s+/_/g;

    my $reserved=( $name =~ m/reserved/i)?1:undef;

    $node = format_node_name($node);
    $name = format_field_name($name);

    if ( $name =~ s/\[(\d+)\.\.(\d+)\]$// ) {
        return  {
                    fname => $name,
                    fsize => $size * ($2 - $1 + 1 ),
                    descr => $descr,
                    subnode => $node,
                    attr => $attr,
                    reserved => $reserved,
                    array => {low_bound => $1, high_bound => $2, esize => $size }
                }
    } else {
        return  {
                    fname => $name,
                    fsize => $size,
                    descr => $descr,
                    subnode => $node,
                    attr => $attr,
                    reserved => $reserved,
                }
    }
}

sub uniform {
    my $arg  = shift;
    my $name = shift;

    my ($bytes, $bits) = (split /\./, $arg, 2);

    $bytes = convert2num( $bytes );
    $bits  = convert2num( $bits );

    die "Unable to parse field size $arg <$name>\n" unless ($bytes || $bits) ;

    return $bytes*8 + $bits;
}

sub convert2num
{
    my $val = shift;
    
    $val ||= 0;
    $val = oct($val) if $val =~ /^0x/i;
    $val += 0;

    return $val;
}

sub size2str {
    my $val = shift;

    my $bytes = int( $val / 32 ) * 4;
    my $bits  = $val % 32;

    my $out = sprintf("0x%04x.%d", $bytes, $bits);

    $out =~ s/^0x0000\././;
    $out =~ s/\.0$//;
    $out ||= "0";

    return $out;
    
}

my %headers = (
        name => "Full Name                           ",
        def  => "Default    ",
        val  => "Value      ",
        addr => "Address    ",
        size => "Size       ",
        RO   => "r/o  ",
        descr=> "Description",
        );

my @default_fmt = qw ( name val addr size RO descr );

sub format_header {

    my @fmt   = @_ ? @_ : @default_fmt;

    my @text = ( "#", @headers{@fmt} );

    chop($text[1]);

    return join("", @text);
}

sub format_field {

    my $name  = shift;
    my $addr  = shift;
    my $field = shift;
    my @fmt   = @_ ? @_ : @default_fmt;

    my $descr = $field->{descr};
    my $size  = $field->{array} ? $field->{array}->{esize} : $field->{fsize};
    my $attr  = $field->{attr};

    my @text = ();
       
    for my $fmt (@fmt) {
        if($fmt eq "name") {
            push @text, $name . " " x (35 - length($name));
        } elsif($fmt eq "addr") {
            my $item = size2str($addr);
            push @text, $item . " " x (10 - length($item));
        } elsif($fmt eq "size") {
            my $item = $size;
            push @text, $item . " " x (10 - length($item));
        } elsif($fmt eq "RO") {
            my $item = $attr =~ /attr_RO/ ? "RO" : "RW";
            push @text, $item . " " x (4 - length($item));
        } elsif($fmt eq "def" || $fmt eq "val" ) {
            my ($item) = $attr =~ /attr_def_(\S+)/;
            $item  = "" unless defined $item;
            push @text, $item . " " x (10 - length($item));
        } elsif($fmt eq "descr") {
            push @text, "# " . $descr;
        }
    }
    return join(" ", @text);
}
# use Data::Dumper;
# print Data::Dumper::DumperX($csp->node_by_name('IB_port_info_GUID_info'));

sub find_roots {
  my $csp = shift;
  my @root_nodes=();
  foreach my $n (@{$csp->{node_list}}) {
    $n->{flag} = 1;
  }
  foreach my $n (@{$csp->{node_list}}) {
    foreach my $f ( @{$n->{fields}} ) {
      undef $f->{subnode}->{flag} if($f->{subnode});
    }
  }
  foreach my $n (@{$csp->{node_list}}) {
    push @root_nodes, $n if ($n->{flag});
  }
  return @root_nodes;
}

sub topological_sort {
  my @sorted_nodes=@_;
  foreach my $n (@sorted_nodes) {
    undef $n->{flag};
  }

  foreach my $n (@sorted_nodes) {
    $n->{flag}=1;
    foreach my $f ( @{$n->{fields}} ) {
      my $subnode=$f->{subnode};
      if ($subnode and not defined($subnode->{flag})) { 
        $subnode->{flag}=1;
        push @sorted_nodes, $subnode;
      }
    }
  }
  return @sorted_nodes;
}

#This does not change case
#
#sub format_name {
#  my $l= shift @_;
#  $l =~ s/([a-z])([A-Z])/$1_$2/g;
#  $l =~ s/__/_/g;
#  $l =~ s/\b_+//;
#  $l =~ s/_+\b//;
#  return $l;
#}

#This converts everything to lower case
sub lc_format_name {
  my $l= shift @_;
  return $l if (not defined $convert_names);
  $l =~ s/([a-z])([A-Z])/$1_\l$2/g;
  $l =~ s/__/_/g;
  $l =~ s/\b_+//;
  $l =~ s/_+\b//;
  return lc $l;
}

#This converts everything to upper case
sub uc_format_name {
  my $l= shift @_;
  return $l if (not defined $convert_names);
  $l =~ s/([a-z])([A-Z])/\u$1_$2/g;
  $l =~ s/__/_/g;
  $l =~ s/\b_+//;
  $l =~ s/_+\b//;
  return uc $l;
}

sub format_node_name {
  return lc_format_name(@_);
}

sub format_field_name {
  return lc_format_name(@_);
}

1;
