#include "test_boost.h"

using namespace std;

// test git step 2.
// test git step 2-1.

void TestObj::runThread1()
{
	boost::this_thread::sleep(boost::posix_time::seconds(1));

	boost::shared_ptr<int> temp = user_.lock();
    boost::shared_ptr<int> temp1 = boost::static_pointer_cast<int>(temp);

	if (temp) {
		printf("temp. \n");
        *temp = 50;
	}
	else {
		printf("temp is null. \n");
	}

	return;
}

void test_thread()
{
    TestObj test_obj;
    boost::shared_ptr<int> temp(new int);
    *temp = 100;
    
    test_obj.user_ = temp;
    test_obj.thread1_ = boost::thread(&TestObj::runThread1, &test_obj);
    
    //boost::this_thread::sleep(boost::posix_time::seconds(2));
    temp.reset();
    boost::this_thread::sleep(boost::posix_time::seconds(5));
    
    if (temp)
        printf("main, temp=%d. \n", *temp);

    boost::shared_ptr<int> temp2 = test_obj.user_.lock();
    if (temp2)
        printf("main, temp=%d. \n", *temp2);
    
    test_obj.thread1_.join();
}

int bind_call(int a, char *b)
{
    printf("[%s()] a=%d, b=%s. \n", __FUNCTION__, a, b);
    
    return a;
}

void test_bind()
{
    boost::function<int (int, char *)> call_func_;
    
    // error
    // void *func_ptr = (void *)bind_call;
    // call_func_ = bind(func_ptr, _1, _2);
    
    call_func_ = boost::bind(bind_call, _1, _2);
    
    call_func_(1, "james");
    
    demo_class dc;
    call_back_factory cbf;

    dc.accept(boost::bind(&call_back_factory::call_back_func1, &cbf, _1));
    dc.run();
    
    dc.accept(boost::bind(&call_back_factory::call_back_func2, cbf, _1, 5));
    dc.run();
}

void test_xml()
{
    boost::property_tree::ptree head_tree, model_child;
    stringstream ss;

    try {
        boost::property_tree::xml_parser::read_xml("../model_def_account.xml", head_tree, 
			boost::property_tree::xml_parser::no_comments | boost::property_tree::xml_parser::trim_whitespace);
    }
    catch(boost::exception const&  ex) {
        std::cout << "read_xml error." << std::endl;
        return;
    }
    
    if (head_tree.empty())
        return;

    model_child = head_tree.get_child("model");

    for (boost::property_tree::ptree::iterator itr=model_child.begin(); itr!=model_child.end(); itr++) {
        boost::property_tree::ptree account = itr->second;
        ss.str(""); ss << "username=" << account.get<string>("username") << ", password=" << account.get<string>("password") << ", list_name=" << account.get<string>("list_name");
        std::cout << ss.str() << std::endl;
    }
}

int OhMetadataParser::XmlWriteCgi(const boost::property_tree::ptree &pt, std::list<std::string> &hstr_list, std::stringstream &out)
{
	int err = TRUE;

	BOOST_FOREACH(const boost::property_tree::ptree::value_type &v, pt) {
	
		hstr_list.push_back(v.first);

		if (v.second.empty()) {
			list<string>::iterator hstr_it = hstr_list.begin();
			while (hstr_it != hstr_list.end()) {
				if (hstr_it != --hstr_list.end())
					out << *hstr_it << ".";
				else
					out << *hstr_it << "=" << v.second.data() << "\n";

				hstr_it++;
			}
		}
		else {
			err = XmlWriteCgi(v.second, hstr_list, out);
			if (err != TRUE) {
				break;
			}

			if (v.second.data().length() > 0) {
				list<string>::iterator hstr_it = hstr_list.begin();
				while (hstr_it != hstr_list.end()) {
					if (hstr_it != --hstr_list.end())
						out << *hstr_it << ".";
					else
						out << *hstr_it << "=" << v.second.data() << "\n";

					hstr_it++;
				}
			}
		}

		hstr_list.pop_back();
	}

	return err;
}

int OhMetadataParser::XmlWriteCgi(std::stringstream &in, std::stringstream &out)
{
	int err = TRUE;

	boost::property_tree::ptree pt;
	std::stringstream ss;
	std::list<string> hstr_list;

	hstr_list.clear();

	do 
	{
		try {
			boost::property_tree::xml_parser::read_xml(
				in, pt,
				boost::property_tree::xml_parser::no_comments | boost::property_tree::xml_parser::trim_whitespace);
		}
		catch (boost::exception const &ex) {
			std::cout << "read_xml error." << std::endl;
			err = FALSE;
			return err;
		}

		err = XmlWriteCgi(pt, hstr_list, out);
	} while (0);

	return err;
}

int OhMetadataParser::CgiWriteXml(const std::stringstream &in, std::stringstream &out)
{
	int err = TRUE;

	boost::property_tree::ptree pt;
	std::string in_str;
	std::map<string, string> keyvalue;

	do 
	{
	    in_str = in.str();
		boost::char_separator<char> sep("\n");
		boost::tokenizer<boost::char_separator<char> > tok(in_str, sep);

		vector<std::string> tok1;

		for (BOOST_AUTO(pos, tok.begin()); pos != tok.end(); pos++) {
			boost::split(tok1, *pos, boost::is_any_of("="), boost::token_compress_on);
			
			boost::optional<std::string> v = pt.get_optional<std::string>(tok1[0]);
			if (v) {
				pt.add(tok1[0], tok1[1]);
			}
			else {
				pt.put(tok1[0], tok1[1]);
			}
		}

		boost::property_tree::xml_parser::write_xml(out, pt);

		/*vector<std::string> rs;
		boost::split(rs, in.str(), boost::is_any_of("\n"), boost::token_compress_on);
		for (vector<std::string>::iterator it = rs.begin(); it != rs.end(); ++it) {
		boost::split(rs, in.str(), boost::is_any_of("="), boost::token_compress_on);
		cout << *it << endl;
		}*/

		/*vector<pair<string::const_iterator, string::const_iterator> > tokens;
		boost::split(tokens, in.str(), boost::is_any_of("="));
		for (auto beg = tokens.begin(); beg != tokens.end(); ++beg) {
		cout << string(beg->first, beg->second) << endl;
		}*/

		/*for (const std::string &tag : boost::split(in.str(), "\n")) {
		auto key_val = boost::split(tag, "=");
		cout << key_val[0] << ", " << key_val[1];
		}*/
		
		/*std::string s = in.str();
		boost::char_separator<char> sep("\n");
		boost::tokenizer<boost::char_separator<char> > tokens(s, sep);
		for (boost::tokenizer<boost::char_separator<char> >::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
			std::cout << "<" << *tok_iter << "> ";
		std::cout << "\n";*/

	} while (0);

	return err;
}

void test_xml2()
{
	int err = TRUE;

	std::stringstream in_ss;
	std::stringstream out_ss;

	std::string xml_str =
		"<StreamingChannel>"
		"<name>james</name>"
		"<id opt=\"1,2\">1</id>"
		"<channelName min=\"0\" max=\"32\">IPdome</channelName>"
		"<enabled opt=\"true\">true</enabled>"
		"<Transport>"
		"<rtspPortNo min=\"0\" max=\"65535\" def=\"554\">554</rtspPortNo>"
		"<maxPacketSize opt=\"1000\">1000</maxPacketSize>"
		"<sourcePortNo min=\"0\" max=\"65535\" def=\"8200\">8200</sourcePortNo>"
		"<ControlProtocolList>"
		"<ControlProtocol>"
		"<streamingTransport opt=\"RTSP\">RTSP</streamingTransport>"
		"</ControlProtocol>"
		"</ControlProtocolList>"
		"<Unicast>"
		"<enabled opt=\"true\">true</enabled>"
		"</Unicast>"
		"<Multicast>"
		"<enabled opt=\"true\" def=\"true\">true</enabled>"
		"<destIPAddress min=\"8\" max=\"16\">0.0.0.0</destIPAddress>"
		"<destPortNo min=\"0\" max=\"65535\" def=\"8600\">8200</destPortNo>"
		"</Multicast>"
		"</Transport>"
		"<Video>"
		"<enabled opt=\"true\">true</enabled>"
		"<videoInputChannelID opt=\"1\">1</videoInputChannelID>"
		"<videoCodecType opt=\"H.264\">H.264</videoCodecType>"
		"<videoScanType opt=\"progressive\">progressive</videoScanType>"
		"<videoResolutionWidth opt=\"1280*720,1920*1080\">1920</videoResolutionWidth>"
		"<videoResolutionHeight opt=\"1280*720,1920*1080\">1080</videoResolutionHeight>"
		"<videoQualityControlType opt=\"CBR,VBR\">VBR</videoQualityControlType>"
		"<constantBitRate min=\"32\" max=\"12288\">4096</constantBitRate>"
		"<fixedQuality opt=\"1,20,40,60,80,100\">80</fixedQuality>"
		"<maxFrameRate opt=\"3000,2500,2200,2000,1800,1600,1500,1200,1000,800,600,400,200,100,50,25,12,6\">3000</maxFrameRate>"
		"<keyFrameInterval min=\"2\" max=\"250\">30</keyFrameInterval>"
		"<BPFrameInterval opt=\"0,1,2\">0</BPFrameInterval>"
		"<snapShotImageType opt=\"JPEG\" def=\"JPEG\">JPEG</snapShotImageType>"
		"<SVC>"
		"<enabled opt=\"ture,false\">false</enabled>"
		"</SVC>"
		"</Video>"
		"<Audio>"
		"<enabled opt=\"true,false\">true</enabled>"
		"<audioInputChannelID opt=\"11\">11</audioInputChannelID>"
		"<audioCompressionType opt=\"G.722.1,G.711ulaw,G.711alaw,MP2L2,G.726,AAC\">G.711alaw</audioCompressionType>"
		"</Audio>"
		"</StreamingChannel>";

	in_ss << xml_str;

	OhMetadataParser oh_meta_parser;
	
	err = oh_meta_parser.XmlWriteCgi(in_ss, out_ss);
	if (err != TRUE) 
		return;

	err = oh_meta_parser.CgiWriteXml(out_ss, in_ss);
	if (err != TRUE)
		return;
}

int main(void) {

	printf("ready go to test boost!. \n");

    test_thread();
	
    test_xml();

	test_xml2();

    system("PAUSE");

	return EXIT_SUCCESS;
}
