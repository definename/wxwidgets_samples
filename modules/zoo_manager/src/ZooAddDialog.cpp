#include "pch.h"
#include "ZooAddDialog.h"
#include "ZooAddPanel.h"

namespace zoo
{

ZooAddDialog::ZooAddDialog(wxWindow* parent)
	: wxDialog(parent, wxID_ANY, wxT("Add dialog"), wxDefaultPosition, wxSize(400, 180))
	, zooAddPanel_(new ZooAddPanel(this)) {
}

ZooAddDialog::~ZooAddDialog() {

}

} // namespace zoo
