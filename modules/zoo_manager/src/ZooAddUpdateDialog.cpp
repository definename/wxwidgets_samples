#include "pch.h"
#include "ZooAddUpdateDialog.h"
#include "ZooAddUpdatePanel.h"
#include "ZooTypes.h"

namespace zoo
{

ZooAddUpdateDialog::ZooAddUpdateDialog(wxWindow* parent, const ZooDataPtr zooData /*= nullptr*/)
	: wxDialog(parent, wxID_ANY, wxT("Add dialog"), wxDefaultPosition, wxSize(400, 180))
	, zooAddUpdatePanel_(new ZooAddUpdatePanel(this)) {

	if (zooData) {
		zooAddUpdatePanel_->SetName(zooData->name_);
		zooAddUpdatePanel_->SetGender(zooData->gender_);
		zooAddUpdatePanel_->SetAge(zooData->age_);
		zooAddUpdatePanel_->SetCell(zooData->cell_);
	}
}

ZooAddUpdateDialog::~ZooAddUpdateDialog() {

}

ZooDataPtr ZooAddUpdateDialog::GetZooData() const {
	ZooDataPtr zooData = std::make_shared<ZooData>(
		zooAddUpdatePanel_->GetName().ToStdWstring(),
		zooAddUpdatePanel_->GetGender().ToStdWstring(),
		zooAddUpdatePanel_->GetAge().ToStdWstring(),
		zooAddUpdatePanel_->GetCell().ToStdWstring());
	return zooData;
}

} // namespace zoo
