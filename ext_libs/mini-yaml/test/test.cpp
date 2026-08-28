#include "gtest/gtest.h"
#include "../yaml/Yaml.hpp"
#include <iostream>
#include <fstream>

/*
Yaml 1.0 spec notes:

*   Multi-line scalars with no token"|(+-) <(+-)" has not newline in end or after each row(uses spaces).
    |   token = 1 newline.
    |-  token = 0 newlines.
    |+  token = 2 newlines.
    >   token, same as | but with spaces instead of newlines after each row.

* An escaped newline is ignored. \ = last character of line.

*/

TEST(Exception, throw)
{
    {
        try
        {
            throw Yaml::InternalException("internal");
        }
        catch(const Yaml::Exception & e)
        {
            EXPECT_EQ(e.Type(), Yaml::Exception::InternalError);
            EXPECT_STREQ(e.what(), "internal");
            EXPECT_STREQ(e.Message(), "internal");
        }
    }
    {
        try
        {
            throw Yaml::ParsingException("parsing");
        }
        catch(const Yaml::Exception & e)
        {
            EXPECT_EQ(e.Type(), Yaml::Exception::ParsingError);
            EXPECT_STREQ(e.what(), "parsing");
            EXPECT_STREQ(e.Message(), "parsing");
        }
    }
    {
        try
        {
            throw Yaml::OperationException("operation");
        }
        catch(const Yaml::Exception & e)
        {
            EXPECT_EQ(e.Type(), Yaml::Exception::OperationError);
            EXPECT_STREQ(e.what(), "operation");
            EXPECT_STREQ(e.Message(), "operation");
        }
    }
}

TEST(Node, Type)
{
    {
        Yaml::Node node;
        EXPECT_EQ(node.Type(), Yaml::Node::None);
        EXPECT_TRUE(node.IsNone());
        EXPECT_FALSE(node.IsSequence());
        EXPECT_FALSE(node.IsMap());
        EXPECT_FALSE(node.IsScalar());
        node.Clear();
        EXPECT_EQ(node.Type(), Yaml::Node::None);
    }
    {
        Yaml::Node node = "test";
        EXPECT_EQ(node.Type(), Yaml::Node::ScalarType);
        EXPECT_FALSE(node.IsNone());
        EXPECT_FALSE(node.IsSequence());
        EXPECT_FALSE(node.IsMap());
        EXPECT_TRUE(node.IsScalar());
        node.Clear();
        EXPECT_EQ(node.Type(), Yaml::Node::None);
    }
    {
        Yaml::Node node;
        node.PushBack();
        EXPECT_EQ(node.Type(), Yaml::Node::SequenceType);
        EXPECT_FALSE(node.IsNone());
        EXPECT_TRUE(node.IsSequence());
        EXPECT_FALSE(node.IsMap());
        EXPECT_FALSE(node.IsScalar());
        node.Clear();
        EXPECT_EQ(node.Type(), Yaml::Node::None);
    }
    {
        Yaml::Node node;
        node["test"];
        EXPECT_EQ(node.Type(), Yaml::Node::MapType);
        EXPECT_FALSE(node.IsNone());
        EXPECT_FALSE(node.IsSequence());
        EXPECT_TRUE(node.IsMap());
        EXPECT_FALSE(node.IsScalar());
        node.Clear();
        EXPECT_EQ(node.Type(), Yaml::Node::None);
    }
}

TEST(Node, As)
{
    {
        Yaml::Node node = "Hello world!";
        EXPECT_EQ(node.As<std::string>(), "Hello world!");
        node = std::string("Foo bar.");
        EXPECT_EQ(node.As<std::string>(), "Foo bar.");
        node = std::string("");
        EXPECT_EQ(node.As<std::string>("empty"), "empty");
    }
    {
        Yaml::Node node = "123456";
        EXPECT_EQ(node.As<int>(), 123456);
        node = "-123456";
        EXPECT_EQ(node.As<int>(), -123456);
        node = "invalid";
        EXPECT_EQ(node.As<int>(123), 123);
    }
    {
        Yaml::Node node = "123.45";
        EXPECT_EQ(node.As<float>(), 123.45f);
        EXPECT_EQ(node.As<int>(), 123);
        node = "-123.45";
        EXPECT_EQ(node.As<float>(), -123.45f);
        EXPECT_EQ(node.As<int>(), -123);
        node = "invalid";
        EXPECT_EQ(node.As<float>(999.1f), 999.1f);
    }
}

TEST(Node, Size)
{
    {
        Yaml::Node node;
        EXPECT_EQ(node.Size(), 0);
        node.PushBack();
        EXPECT_EQ(node.Size(), 1);
        node.PushBack();
        EXPECT_EQ(node.Size(), 2);
        node.Erase(1);
        EXPECT_EQ(node.Size(), 1);
        node.Erase(0);
        EXPECT_EQ(node.Size(), 0);

        node.Insert(10);
        EXPECT_EQ(node.Size(), 1);
        node.Erase(1);
        EXPECT_EQ(node.Size(), 1);
        node.Erase(0);
        EXPECT_EQ(node.Size(), 0);

        node.PushBack();
        node.PushBack();
        node.Clear();
        EXPECT_EQ(node.Size(), 0);
    }
    {
        Yaml::Node node;
        EXPECT_EQ(node.Size(), 0);
        node["test"];
        EXPECT_EQ(node.Size(), 1);
        node["test"];

        EXPECT_EQ(node.Size(), 1);
        node["foo bar"];
        EXPECT_EQ(node.Size(), 2);

        node.Erase("hello world");
        EXPECT_EQ(node.Size(), 2);

        node.Erase("test");
        EXPECT_EQ(node.Size(), 1);
        node.Erase("foo bar");
        EXPECT_EQ(node.Size(), 0);

        node["foo bar"];
        EXPECT_EQ(node.Size(), 1);
        node.Clear();
        EXPECT_EQ(node.Size(), 0);
    }
    {
        Yaml::Node node = "test";
        EXPECT_EQ(node.Size(), 0);
    }
}

void Compare_Node_Copy(Yaml::Node & node)
{
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.Size(), 3);


    Yaml::Node & item_1 = node[0];
    EXPECT_TRUE(item_1.IsScalar());
    EXPECT_EQ(item_1.As<std::string>(), "item 1");

    {
        Yaml::Node & item_2 = node[1];
        EXPECT_TRUE(item_2.IsMap());
        EXPECT_EQ(item_2.Size(), 1);

        Yaml::Node & key = item_2["key"];
        EXPECT_TRUE(key.IsSequence());
        EXPECT_EQ(key.Size(), 2);

        Yaml::Node & item_2_1 = key[0];
        EXPECT_TRUE(item_2_1.IsScalar());
        EXPECT_EQ(item_2_1.As<std::string>(), "item 2.1");

        Yaml::Node & item_2_2 = key[1];
        EXPECT_TRUE(item_2_2.IsMap());
        EXPECT_EQ(item_2_2.Size(), 1);

        Yaml::Node & key_two = item_2_2["key two"];
        EXPECT_TRUE(key_two.IsScalar());
        EXPECT_EQ(key_two.As<std::string>(), "item 2.2");
    }

    Yaml::Node & item_3 = node[2];
    EXPECT_TRUE(item_3.IsScalar());
    EXPECT_EQ(item_3.As<std::string>(), "item 3");
}

TEST(Node, Copy_1)
{
    {
        Yaml::Node root;
        root["key 1"] = "value 1";
        root["key 2"] = "value 2";
        root["key 3"] = "value 3";

        {
            Yaml::Node copy(root);

            EXPECT_TRUE(copy.IsMap());

            Yaml::Node & key_1 = copy["key 1"];
            EXPECT_TRUE(key_1.IsScalar());
            EXPECT_EQ(key_1.As<std::string>(), "value 1");

            Yaml::Node & key_2 = copy["key 2"];
            EXPECT_TRUE(key_2.IsScalar());
            EXPECT_EQ(key_2.As<std::string>(), "value 2");

            Yaml::Node & key_3 = copy["key 3"];
            EXPECT_TRUE(key_3.IsScalar());
            EXPECT_EQ(key_3.As<std::string>(), "value 3");
        }
    }

    {
        Yaml::Node root;
        root.PushBack() = "item 1";
        root.PushBack() = "item 2";
        root.PushBack() = "item 3";

        {
            Yaml::Node copy(root);

            EXPECT_TRUE(copy.IsSequence());
            EXPECT_EQ(copy.Size(), 3);

            Yaml::Node & item_1 = copy[0];
            EXPECT_TRUE(item_1.IsScalar());
            EXPECT_EQ(item_1.As<std::string>(), "item 1");

            Yaml::Node & item_2 = copy[1];
            EXPECT_TRUE(item_2.IsScalar());
            EXPECT_EQ(item_2.As<std::string>(), "item 2");

            Yaml::Node & item_3 = copy[2];
            EXPECT_TRUE(item_3.IsScalar());
            EXPECT_EQ(item_3.As<std::string>(), "item 3");
        }
    }

    {
        Yaml::Node root;
        root.PushBack() = "item 1";
        Yaml::Node & map = root.PushBack()["key"];
        map.PushBack() = "item 2.1";
        map.PushBack()["key two"] = "item 2.2";
        root.PushBack() = "item 3";

        {
            Yaml::Node copy(root);
            Compare_Node_Copy(copy);
        }

        {
            Yaml::Node assign;
            assign = root;
            Compare_Node_Copy(assign);
        }
    }
}

void Parse_File_learnyaml(Yaml::Node & root)
{
    Yaml::Node & key = root["key"];
    EXPECT_TRUE(key.IsScalar());
    EXPECT_EQ(key.As<std::string>(), "value");

    Yaml::Node & another_key = root["another_key"];
    EXPECT_TRUE(another_key.IsScalar());
    EXPECT_EQ(another_key.As<std::string>(), "Another value goes here.");

    Yaml::Node & a_number_value = root["a_number_value"];
    EXPECT_TRUE(a_number_value.IsScalar());
    EXPECT_EQ(a_number_value.As<int>(), 100);

    Yaml::Node & scientific_notation = root["scientific_notation"];
    EXPECT_TRUE(scientific_notation.IsScalar());
    EXPECT_EQ(scientific_notation.As<std::string>(), "1e+12");

    Yaml::Node & boolean = root["boolean"];
    EXPECT_TRUE(boolean.IsScalar());
    EXPECT_EQ(boolean.As<std::string>(), "true");
    EXPECT_EQ(boolean.As<bool>(), true);

    // Null values are handled as strings.
    Yaml::Node & null_value = root["null_value"];
    EXPECT_TRUE(null_value.IsScalar());
    EXPECT_EQ(null_value.As<std::string>(), "null");

    Yaml::Node & key_with_spaces = root["key with spaces"];
    EXPECT_TRUE(key_with_spaces.IsScalar());
    EXPECT_EQ(key_with_spaces.As<std::string>(), "value");

    Yaml::Node & keys_can_be_quoted_too = root["Keys: can be \"quoted\" too."];
    EXPECT_TRUE(keys_can_be_quoted_too.IsScalar());
    EXPECT_EQ(keys_can_be_quoted_too.As<std::string>(), "Useful if you want to put a ':' in your key. Or use comment char(#).");

    Yaml::Node & scalar_block = root["scalar_block"];
    EXPECT_TRUE(scalar_block.IsScalar());
    EXPECT_EQ(scalar_block.As<std::string>(), "block of text will separate all lines with spaces.");

    Yaml::Node & literal_block = root["literal_block"];
    EXPECT_TRUE(literal_block.IsScalar());
    EXPECT_EQ(literal_block.As<std::string>(),  "This entire block of text will be the value of the 'literal_block' key,      \n"
                                                "with line breaks being preserved.\n\n"
                                                "The literal continues until de-dented, and the leading indentation is\n"
                                                "stripped.\n\n"
                                                "    Any lines that are 'more-indented' keep the rest of their indentation -\n"
                                                "    these lines will be indented by 4 spaces.\n");

    Yaml::Node & folded_style = root["folded_style"];
    EXPECT_TRUE(folded_style.IsScalar());
    EXPECT_EQ(folded_style.As<std::string>(),   "This entire block of text will be the value of 'folded_style', but this time, all newlines will be replaced with a single space.\n"
                                                "Blank lines, like above, are converted to a newline character.\n\n"
                                                "    'More-indented' lines keep their newlines, too -\n"
                                                "    this text will appear over two lines.\n");

    {
        Yaml::Node & a_nested_map = root["a_nested_map"];
        EXPECT_TRUE(a_nested_map.IsMap());
        EXPECT_EQ(a_nested_map.Size(), 3);

        Yaml::Node & key = a_nested_map["key"];
        EXPECT_TRUE(key.IsScalar());
        EXPECT_EQ(key.As<std::string>(), "value");

        Yaml::Node & another_key = a_nested_map["another_key"];
        EXPECT_TRUE(another_key.IsScalar());
        EXPECT_EQ(another_key.As<std::string>(), "Another Value");

        Yaml::Node & another_nested_map = a_nested_map["another_nested_map"];
        EXPECT_TRUE(another_nested_map.IsMap());
        EXPECT_EQ(another_nested_map.Size(), 1);

        Yaml::Node & hello = another_nested_map["hello"];
        EXPECT_TRUE(hello.IsScalar());
        EXPECT_EQ(hello.As<std::string>(), "hello");
    }

    // Not allowing floats as keys, read as string.
    Yaml::Node & point_twenty_five = root["0.25"];
    EXPECT_TRUE(point_twenty_five.IsScalar());
    EXPECT_EQ(point_twenty_five.As<std::string>(), "a float key");

    {
        Yaml::Node & a_sequence = root["a_sequence"];
        EXPECT_TRUE(a_sequence.IsSequence());
        EXPECT_EQ(a_sequence.Size(), 6);

        Yaml::Node & item_1 = a_sequence[0];
        EXPECT_TRUE(item_1.IsScalar());
        EXPECT_EQ(item_1.As<std::string>(), "Item 1");

        Yaml::Node & item_2 = a_sequence[1];
        EXPECT_TRUE(item_2.IsScalar());
        EXPECT_EQ(item_2.As<std::string>(), "Item 2");

        Yaml::Node & item_3 = a_sequence[2];
        EXPECT_TRUE(item_3.IsScalar());
        EXPECT_EQ(item_3.As<std::string>(), "0.5");
        EXPECT_EQ(item_3.As<float>(), 0.5f);

        Yaml::Node & item_4 = a_sequence[3];
        EXPECT_TRUE(item_4.IsScalar());
        EXPECT_EQ(item_4.As<std::string>(), "Item 4");

        Yaml::Node & item_5 = a_sequence[4];
        EXPECT_TRUE(item_5.IsMap());
        EXPECT_EQ(item_5.Size(), 2);

        Yaml::Node & key = item_5["key"];
        EXPECT_TRUE(key.IsScalar());
        EXPECT_EQ(key.As<std::string>(), "value");

        Yaml::Node & another_key = item_5["another_key"];
        EXPECT_TRUE(another_key.IsScalar());
        EXPECT_EQ(another_key.As<std::string>(), "another_value");

        Yaml::Node & item_6 = a_sequence[5];
        EXPECT_TRUE(item_6.IsSequence());
        EXPECT_EQ(item_6.Size(), 2);

        Yaml::Node & item_6_1 = item_6[0];
        EXPECT_TRUE(item_6_1.IsScalar());
        EXPECT_EQ(item_6_1.As<std::string>(), "This is a sequence");

        Yaml::Node & item_6_2 = item_6[1];
        EXPECT_TRUE(item_6_2.IsScalar());
        EXPECT_EQ(item_6_2.As<std::string>(), "inside another sequence");
    }

    Yaml::Node & datetime = root["datetime"];
    EXPECT_TRUE(datetime.IsScalar());
    EXPECT_EQ(datetime.As<std::string>(), "2001-12-15T02:59:43.1Z");

    Yaml::Node & datetime_with_spaces = root["datetime_with_spaces"];
    EXPECT_TRUE(datetime_with_spaces.IsScalar());
    EXPECT_EQ(datetime_with_spaces.As<std::string>(), "2001-12-14 21:59:43.10 -5");

    Yaml::Node & date = root["date"];
    EXPECT_TRUE(date.IsScalar());
    EXPECT_EQ(date.As<std::string>(), "2002-12-14");

    {
        Yaml::Node & set2 = root["set2"];
        EXPECT_TRUE(set2.IsMap());
        EXPECT_EQ(set2.Size(), 3);

        Yaml::Node & item1 = set2["item1"];
        EXPECT_TRUE(item1.IsScalar());
        EXPECT_EQ(item1.As<std::string>(), "null");

        Yaml::Node & item2 = set2["item2"];
        EXPECT_TRUE(item2.IsScalar());
        EXPECT_EQ(item2.As<std::string>(), "null");

        Yaml::Node & item3 = set2["item3"];
        EXPECT_TRUE(item3.IsScalar());
        EXPECT_EQ(item3.As<std::string>(), "null");
    }
}

TEST(Node, Copy_2)
{

    Yaml::Node root;
    EXPECT_NO_THROW(Yaml::Parse(root, "../test/learnyaml.yaml"));

    {
        Yaml::Node copy(root);
        Parse_File_learnyaml(copy);
    }
    {
        Yaml::Node copy = root;
        Parse_File_learnyaml(copy);
    }


}

TEST(Parse, File)
{
    {
        Yaml::Node root;
        EXPECT_THROW(Yaml::Parse(root, "bad_path_of_file.txt"), Yaml::OperationException);
    }
    {
        Yaml::Node root;
        EXPECT_NO_THROW(Yaml::Parse(root, "../.travis.yml"));
    }
    {
        Yaml::Node root;
        EXPECT_THROW(Yaml::Parse(root, "../yaml/Yaml.hpp"), Yaml::ParsingException);
    }
    {
        Yaml::Node root;
        EXPECT_NO_THROW(Yaml::Parse(root, "../test/learnyaml.yaml"));
    }
}

TEST(Parse, File_learnyaml)
{
    const std::string filename = "../test/learnyaml.yaml";

    {
        Yaml::Node root;
        EXPECT_NO_THROW(Yaml::Parse(root, filename.c_str()));

        Parse_File_learnyaml(root);
    }
    {
        std::ifstream fin(filename, std::ifstream::binary);
        EXPECT_TRUE(fin.is_open());
        if(fin.is_open())
        {
            fin.seekg(0, fin.end);
            size_t dataSize = static_cast<size_t>(fin.tellg());
            fin.seekg(0, fin.beg);
            char * pData = new char [dataSize];
            fin.read(pData, dataSize);
            fin.close();

            Yaml::Node root;
            EXPECT_NO_THROW(Yaml::Parse(root, pData, dataSize));
            delete [] pData;
            Parse_File_learnyaml(root);
        }
    }
    {
        std::ifstream fin(filename, std::ifstream::binary);
        EXPECT_TRUE(fin.is_open());
        if(fin.is_open())
        {
            fin.seekg(0, fin.end);
            size_t dataSize = static_cast<size_t>(fin.tellg());
            fin.seekg(0, fin.beg);
            char * pData = new char [dataSize];
            fin.read(pData, dataSize);
            fin.close();
            std::string data(pData, dataSize);
            delete [] pData;

            // String
            Yaml::Node root_string;
            EXPECT_NO_THROW(Yaml::Parse(root_string, data));
            Parse_File_learnyaml(root_string);

            // Stream
            std::stringstream stream(data);
            Yaml::Node root_stream;
            EXPECT_NO_THROW(Yaml::Parse(root_stream, stream));
            Parse_File_learnyaml(root_stream);
        }
    }
}

TEST(Parse, Invalid)
{
    std::ifstream fin("../test/invalid.yaml", std::ifstream::binary);
    EXPECT_TRUE(fin.is_open());
    if(fin.is_open())
    {
        fin.seekg(0, fin.end);
        size_t dataSize = static_cast<size_t>(fin.tellg());
        fin.seekg(0, fin.beg);
        char * pData = new char [dataSize];
        fin.read(pData, dataSize);
        fin.close();
        std::string data(pData, dataSize);
        delete [] pData;
        std::stringstream stream(data);
        Yaml::Node root_stream;

        const size_t tests = 8;
        size_t loops = 0;
        while(loops < tests)
        {
            loops++;

            //try
            //{
            //    Yaml::Parse(root_stream, stream);
            //}
            //catch(const Yaml::Exception & e)
            //{
            //    std::cout << "Exception(" << e.Type() <<  "): " << e.what() << std::endl;
            //}

            EXPECT_THROW(Yaml::Parse(root_stream, stream), Yaml::ParsingException);

        }
    }
}

TEST(Parse, Valid)
{
    std::ifstream fin("../test/valid.yaml", std::ifstream::binary);
    EXPECT_TRUE(fin.is_open());
    if(fin.is_open())
    {
        fin.seekg(0, fin.end);
        size_t dataSize = static_cast<size_t>(fin.tellg());
        fin.seekg(0, fin.beg);
        char * pData = new char [dataSize];
        fin.read(pData, dataSize);
        fin.close();
        std::string data(pData, dataSize);
        delete [] pData;
        std::stringstream stream(data);
        Yaml::Node root_stream;

        const size_t tests = 8;
        size_t loops = 0;
        while(loops < tests)
        {
            loops++;

            //try
            //{
            //    Yaml::Parse(root_stream, stream);
            //}
            //catch(const Yaml::Exception & e)
            //{
            //    std::cout << "Exception(" << e.Type() <<  "): " << e.what() << std::endl;
            //}

            EXPECT_NO_THROW(Yaml::Parse(root_stream, stream));

        }
    }
}

TEST(Iterator, Iterator)
{
    Yaml::Node root;
    root["key"] = "value";
    root["another_key"] = "Another Value";
    root["another_nested_map"]["key"] = "value";

    EXPECT_TRUE(root.IsMap());
    EXPECT_EQ(root.Size(), 3);

    size_t loops = 0;
    bool flags[3] = {false, false, false};
    for(Yaml::Iterator it = root.Begin(); it != root.End(); it++)
    {
        std::pair<std::string, Yaml::Node&> value = *it;
        const std::string & key = value.first;

        if(key == "key")
        {
            Yaml::Node & node = value.second;
            EXPECT_TRUE(node.IsScalar());
            EXPECT_EQ(node.As<std::string>(), "value");
            flags[0] = true;
        }
        else if(key == "another_key")
        {
            Yaml::Node & node = value.second;
            EXPECT_TRUE(node.IsScalar());
            EXPECT_EQ(node.As<std::string>(), "Another Value");
            flags[1] = true;
        }
        else if(key == "another_nested_map")
        {
            Yaml::Node & node = value.second;
            EXPECT_TRUE(node.IsMap());
            flags[2] = true;
        }

        loops++;
    }

    EXPECT_EQ(loops, 3);
    EXPECT_TRUE(flags[0]);
    EXPECT_TRUE(flags[1]);
    EXPECT_TRUE(flags[2]);

}

TEST(Iterator, ConstIterator)
{
    Yaml::Node root;
    root["key"] = "value";
    root["another_key"] = "Another Value";
    root["another_nested_map"]["key"] = "value";
    const Yaml::Node & constRoot = root;;


    EXPECT_TRUE(constRoot.IsMap());
    EXPECT_EQ(constRoot.Size(), 3);

    size_t loops = 0;
    bool flags[3] = {false, false, false};
    for(Yaml::ConstIterator it = constRoot.Begin(); it != constRoot.End(); it++)
    {
        std::pair<std::string, const Yaml::Node&> value = *it;
        const std::string & key = value.first;

        if(key == "key")
        {
            const Yaml::Node & node = value.second;
            EXPECT_TRUE(node.IsScalar());
            EXPECT_EQ(node.As<std::string>(), "value");
            flags[0] = true;
        }
        else if(key == "another_key")
        {
            const Yaml::Node & node = value.second;
            EXPECT_TRUE(node.IsScalar());
            EXPECT_EQ(node.As<std::string>(), "Another Value");
            flags[1] = true;
        }
        else if(key == "another_nested_map")
        {
            const Yaml::Node & node = value.second;
            EXPECT_TRUE(node.IsMap());
            flags[2] = true;
        }

        loops++;
    }

    EXPECT_EQ(loops, 3);
    EXPECT_TRUE(flags[0]);
    EXPECT_TRUE(flags[1]);
    EXPECT_TRUE(flags[2]);
}

TEST(Serialize, Serialize)
{
    Yaml::Node root;
    EXPECT_NO_THROW(Yaml::Parse(root, "../test/learnyaml.yaml"));

    {
        EXPECT_NO_THROW(Yaml::Serialize(root, "test_learnyaml.yaml"));

        Yaml::Node learn_yaml;
        EXPECT_NO_THROW(Yaml::Parse(learn_yaml, "test_learnyaml.yaml"));
        Parse_File_learnyaml(learn_yaml);
    }
    {
        std::string data = "";
        EXPECT_NO_THROW(Yaml::Serialize(root, data));

        Yaml::Node learn_yaml;
        EXPECT_NO_THROW(Yaml::Parse(learn_yaml, data));
        Parse_File_learnyaml(learn_yaml);
    }
    {
        std::stringstream data;
        EXPECT_NO_THROW(Yaml::Serialize(root, data));

        Yaml::Node learn_yaml;
        EXPECT_NO_THROW(Yaml::Parse(learn_yaml, data));
        Parse_File_learnyaml(learn_yaml);
    }
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
