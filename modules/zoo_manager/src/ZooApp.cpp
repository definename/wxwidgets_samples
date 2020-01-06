#include "pch.h"
#include "ZooApp.h"
#include "ZooFrame.h"

#include "ZooTypes.h"

namespace zoo
{

//! Macro will allow wxWidgets to create the application object during program execution.
wxIMPLEMENT_APP(ZooApp);


int ZooApp::OnExit() {
	return wxApp::OnExit();
}

bool ZooApp::OnInit(void) {
	if (!wxApp::OnInit()) {
		return false;
	}

	{
		using map_t = std::unordered_map<int, ZooData>;
		map_t m;
		std::ofstream ofile("test.dat", std::ios::out | std::ios::binary);
		ZooData zooData(wxT("sdf"), wxT("123"), wxT("123"), wxT("123"));
		m[0] = zooData;
		SerializeTo<boost::archive::binary_oarchive>(m, ofile);

		map_t m1;
		std::ifstream ifile("test.dat", std::ios::in | std::ios::binary);
		DeserializeFrom<boost::archive::binary_iarchive>(ifile, m1);
		wxString s;
		s.Printf("map size:%d name:%s", m1.size(), m1[0].name_);
		wxMessageBox(s);
	}

	wxImage::AddHandler(new wxPNGHandler);

	zooFrame_ = new ZooFrame();
	return zooFrame_->Show(true);
}

} // namespace zoo
