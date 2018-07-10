%{!?ibmadlib: %define ibmadlib libibmad-devel}
%{!?name: %define name mstflint}
%{!?version: %define version 4.10.0}
%{!?release: %define release 1}
%{!?buildtype: %define buildtype "native"}
%{!?noinband: %define noinband 0}
%{!?nodc: %define nodc 0}
%{!?enablecs: %define enablecs 0}
%{!?nopenssl: %define nopenssl 1}
%{!?enablefwmgr: %define enablefwmgr 0}
%{!?CONF_DIR: %define CONF_DIR /etc/mstflint}

%define mstflint_python_tools %{_libdir}/mstflint/python_tools

%define _unpackaged_files_terminate_build 0
%define debug_package %{nil}
%define optflags -g -O2

Summary: Mellanox firmware burning application
Name: %{name}
Version: %{version}
Release: %{release} 
License: GPL/BSD
Url: http://openfabrics.org
Group: System Environment/Base
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}
Source: %{name}-%{version}.tar.gz
ExclusiveArch: i386 i486 i586 i686 x86_64 ia64 ppc ppc64 ppc64le arm64 aarch64
BuildRequires: zlib-devel %{ibmadlib}

%description
This package contains firmware update tool, vpd dump and register dump tools
for network adapters based on Mellanox Technologies chips.

%prep
%setup -q

%build

%if %{nodc}
    config_flags="$config_flags --disable-dc"
%endif

%if %{noinband}
    config_flags="$config_flags --disable-inband"
%endif

%if ! %{nopenssl}
    config_flags="$config_flags --enable-openssl"
%endif

%if %{enablecs}
    config_flags="$config_flags --enable-cs"
%endif

%if %{enablefwmgr}
    config_flags="$config_flags --enable-fw-mgr"
%endif

%if %{buildtype} == "ppc"
    config_flags="$config_flags --host=ppc-linux"
%endif

%if %{buildtype} == "ppc64"
    config_flags="$config_flags --host=ppc64-linux --enable-static-libstdcpp=yes"
%endif

%if %{buildtype} == "ppc64le"
    config_flags="$config_flags --host=powerpc64le-linux-gnu --enable-dynamic-ld=yes"
%endif

%if %{buildtype} == "arm64"
    config_flags="$config_flags --host arm"
%endif

%configure ${config_flags}

make

%install
rm -rf $RPM_BUILD_ROOT
make DESTDIR=${RPM_BUILD_ROOT} install
# remove unpackaged files from the buildroot
rm -f $RPM_BUILD_ROOT%{_libdir}/*.la

# create softlinks to old mtcr header and lib locations
# link mtcr_ul to old location
mkdir -p %{buildroot}/%{_includedir}/mtcr_ul
ln -s %{_includedir}/mstflint/mtcr.h %{buildroot}/%{_includedir}/mtcr_ul/mtcr.h
ln -s %{_includedir}/mstflint/mtcr_com_defs.h %{buildroot}/%{_includedir}/mtcr_ul/mtcr_com_defs.h
# link mtcr_ul to old lib path
ln -s %{_libdir}/mstflint/libmtcr_ul.a %{buildroot}/%{_libdir}/libmtcr_ul.a 

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%{_bindir}/mstmread
%{_bindir}/mstmwrite
%{_bindir}/mstflint
%{_bindir}/mstregdump
%{_bindir}/mstmtserver
%{_bindir}/mstvpd
%{_bindir}/mstmcra
%{_bindir}/mstconfig
%{_bindir}/mstfwreset
%if %{enablefwmgr}
 %{_bindir}/mstfwmanager
%{CONF_DIR}/ca-bundle.crt
%endif

%{_includedir}/mstflint/mtcr.h
%{_includedir}/mstflint/mtcr_com_defs.h
%{_includedir}/mtcr_ul/mtcr.h
%{_includedir}/mtcr_ul/mtcr_com_defs.h
%{_libdir}/mstflint/libmtcr_ul.a
%{_libdir}/libmtcr_ul.a

%{mstflint_python_tools}/tools_version.py
%{mstflint_python_tools}/mstfwreset/mstfwreset.py
%{mstflint_python_tools}/mstfwreset/mlxfwresetlib/*.py
%{mstflint_python_tools}/mtcr.py
%{mstflint_python_tools}/cmtcr.so
%{mstflint_python_tools}/cmdif.py
%{mstflint_python_tools}/ccmdif.so
%{mstflint_python_tools}/regaccess.py
%{mstflint_python_tools}/rreg_access.so
%{mstflint_python_tools}/dev_mgt.py
%{mstflint_python_tools}/c_dev_mgt.so

%{_datadir}/mstflint
%{_mandir}/man1/*

%changelog
* Sun Jul 01 2018 Dan Goldberg <dang@dev.mellanox.co.il>
   MFT 4.10.0 Updates

* Sun Apr 1 2018 Adham Masarwah <adham@dev.mellanox.co.il>
   Adding support for newer device in Secure Boot kernel and mtcr
   
* Mon Jul 17 2017 Adham Masarwah <adham@dev.mellanox.co.il>
   Adding mlxfwreset to mstflint
   
* Mon May 08 2017 Adrian Chiris <adrianc@dev.mellanox.co.il>
   MFT 4.7.0 Updates
   
* Tue Jan 10 2017 Adham Masarwah <adham@dev.mellanox.co.il>
   Removed hca_self_test.ofed installation from the package
    
* Mon Jan 9 2017 Adham Masarwah <adham@dev.mellanox.co.il>
   MFT 4.6.0 Updates
    
* Tue May 17 2016 Adrian Chiris <adrianc@dev.mellanox.co.il>
   MFT 4.4.0 Updates
   
* Wed Mar 23 2016 Adrian Chiris <adrianc@dev.mellanox.co.il>
   MFT 4.4.0 Updates

* Mon Jan 11 2016 Adrian Chiris <adrianc@dev.mellanox.co.il>
   MFT 4.3.0 Updates

* Wed Aug 26 2015 Adrian Chiris <adrianc@dev.mellanox.co.il>
   MFT 4.1.0 Updates
   
* Fri Jun 05 2015 Adrian Chiris <adrianc@dev.mellanox.co.il>
   MFT 4.0.1 Updates

* Thu Feb 05 2015 Adrian Chiris <adrianc@dev.mellanox.co.il>
   MFT 4.0.0 Updates

* Sun Dec 07 2014 Tomer Cohen <tomerc@mellanox.com>
   Added support for multiple architectures

* Sun Oct 12 2014 Oren Kladnitsky <orenk@dev.mellanox.co.il>
   MFT 3.7.1

* Thu Jul 31 2014 Oren Kladnitsky <orenk@dev.mellanox.co.il>
   MFT 3.7.0 Updates

* Mon Mar 31 2014 Oren Kladnitsky <orenk@dev.mellanox.co.il>
   MFT 3.6.0 Updates

* Tue Dec 24 2013 Oren Kladnitsky <orenk@dev.mellanox.co.il>
   MFT 3.5.0 Updates

* Wed Mar 20 2013 Oren Kladnitsky <orenk@dev.mellanox.co.il>
   MFT 3.0.0

* Thu Dec  4 2008 Oren Kladnitsky <orenk@dev.mellanox.co.il>
   Added hca_self_test.ofed installation
   
* Sun Dec 23 2007 Oren Kladnitsky <orenk@dev.mellanox.co.il>
   Added mtcr.h installation
   
* Fri Dec 07 2007 Ira Weiny <weiny2@llnl.gov> 1.0.0
   initial creation

