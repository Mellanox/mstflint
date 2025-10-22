/*
* MIT License
*
* Copyright(c) 2018 Jimmie Bergmann
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files(the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions :
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*/

#include <Yaml.hpp>

using namespace Yaml;

static void Example1();
static void Example2();
static void Example3();
static void Example4();

int main()
{
    Example1();
    Example2();
    Example3();
    Example4();

	return 0;
}

void Example1()
{
    const std::string data =
		"data1 : \t | \t \n"
		"  Hello1\n"
		"   world1.\n"
		"data2 : \t > \t \n"
		"  Hello2\n"
		"   world2.\n"
		"data3: \t |- \t \n"
		"  Hello3\n"
		"   world3.\n"
		"data4 : \t >- \t \n"
		"  Hello4\n"
		"   world4.\n"
		"data5: |\n"
		"   hello: world5\n"
		"    foo: bar5.\n"
		"data6: 123\n"
		"data7: 123.6\n";

    Node root;
    try
    {
        Parse(root, data);
    }
    catch (const Exception e)
    {
        std::cout << "Exception " << e.Type() << ": " << e.what() << std::endl;
        return;
    }

    std::cout << root["data1"].As<std::string>() << std::endl;
    std::cout << root["data2"].As<std::string>() << std::endl;
    std::cout << root["data3"].As<std::string>() << std::endl;
    std::cout << root["data4"].As<std::string>() << std::endl;
    std::cout << root["data5"].As<std::string>() << std::endl;
    std::cout << root["data6"].As<int>(0) << std::endl;
    std::cout << root["data7"].As<float>(0.0f) << std::endl;
}

void Example2()
{
    const std::string data =
		" - Hello world\n"
		" - 123\n"
		" - 123.4\n";

    Node root;
    try
    {
        Parse(root, data);
        if(root.IsSequence() == false)
        {
            throw InternalException("Test: Root is not a sequence.");
        }
    }
    catch (const Exception e)
    {
        std::cout << "Exception " << e.Type() << ": " << e.what() << std::endl;
        return;
    }

    std::cout << root[0].As<std::string>() << std::endl;
    std::cout << root[1].As<int>(0) << std::endl;
    std::cout << root[2].As<float>(0.0f) << std::endl;
}

void Example3()
{
    const std::string data =
        "data1: \n"
        "  123\n"
        "data2: Hello world\n"
        "data3:\n"
        "   - key1: 123\n"
        "     key2: Test\n"
		"   - Hello world\n"
		"   - 123\n"
		"   - 123.4\n";

    Node root;
    try
    {
        Parse(root, data);
    }
    catch (const Exception e)
    {
        std::cout << "Exception " << e.Type() << ": " << e.what() << std::endl;
        return;
    }

    std::cout << root["data1"].As<int>(0) << std::endl;
    std::cout << root["data2"].As<std::string>() << std::endl;
    std::cout << root["data3"][0]["key1"].As<int>(0) << std::endl;
    std::cout << root["data3"][0]["key2"].As<std::string>() << std::endl;
    std::cout << root["data3"][1].As<std::string>() << std::endl;
    std::cout << root["data3"][2].As<int>(0) << std::endl;
    std::cout << root["data3"][3].As<float>(0.0f) << std::endl;
}

void Example4()
{
    Node root;
    try
    {
        Parse(root, "../examples/data1.txt");
    }
    catch (const Exception e)
    {
        std::cout << "Exception " << e.Type() << ": " << e.what() << std::endl;
        return;
    }

    try
    {
        Node & server = root["server"];
        Node & services = root["services"];

        if(server.IsMap() == false)
        {
            throw InternalException("Server is not of type Map.");
        }
        if(services.IsSequence() == false)
        {
            throw InternalException("Services is not of type sequence.");
        }

        std::cout << "Server:" << std::endl;
        std::cout << "  max connections: " << server["max_connections"].As<int>(0) << std::endl;
        std::cout << "  com port       : " << server["com_port"].As<unsigned short>(0) << std::endl;

        std::cout << "Services:" << std::endl;
        //for(size_t i = 0; i < services.Size(); i++)
        size_t countS = 0;
        for(auto itS = services.Begin(); itS != services.End(); itS++)
        {
            std::cout << " Service " << countS++ << std::endl;
            Node & service = (*itS).second;

           /* for(auto itSS = service.Begin(); itSS != service.End(); itSS++)
            {
                std::cout << "  " << (*itSS).first << ":  " << (*itSS).second.As<std::string>() << std::endl;
            }*/

            std::cout << "  enabled:         " << service["enabled"].As<bool>(false) << std::endl;
            std::cout << "  name:            " << service["name"].As<std::string>() << std::endl;
            std::cout << "  protocol:        " << service["protocol"].As<std::string>() << std::endl;
            std::cout << "  host:            " << service["host"].As<std::string>() << std::endl;
            std::cout << "  port:            " << service["port"].As<unsigned short>(0) << std::endl;
            std::cout << "  balancing:       " << service["balancing"].As<std::string>("No balancing value.") << std::endl;
            std::cout << "  max_connections: " << service["max_connections"].As<int>(99999) << std::endl;
            std::cout << "  session:         " << service["session"].As<std::string>("No session value.") << std::endl;

            Node & nodes = service["nodes"];
            if(nodes.IsSequence() == false)
            {
                throw InternalException("Nodes is not of type sequence.");
            }

            std::cout << "  Nodes:" << std::endl;
            //for(size_t i = 0; i < nodes.Size(); i++)
            size_t countN = 0;
            for(auto itN = nodes.Begin(); itN != nodes.End(); itN++)
            {
                std::cout << "   Node " << countN++ << std::endl;
                Node & node = (*itN).second;//nodes[i];

                std::cout << "    name:      " << node["name"].As<std::string>() << std::endl;
                std::cout << "    protocol:  " << node["protocol"].As<std::string>() << std::endl;
                std::cout << "    host:      " << node["host"].As<std::string>() << std::endl;
                std::cout << "    port:      " << node["port"].As<unsigned short>(0) << std::endl;
                std::cout << std::endl;
            }

            std::cout << std::endl;
        }

    }
    catch (const Exception e)
    {
        std::cout << "Example exception " << e.Type() << ": " << e.what() << std::endl;
        return;
    }


    try
    {
        Serialize(root, "../bin/out.txt");
    }
    catch (const Exception e)
    {
        std::cout << "Exception " << e.Type() << ": " << e.what() << std::endl;
        std::cin.get();
    }

}



