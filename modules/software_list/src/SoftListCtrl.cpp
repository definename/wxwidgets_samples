#include "pch.h"
#include "SoftListCtrl.h"
#include "SoftScanner.h"

namespace soft
{

wxBEGIN_EVENT_TABLE(SoftListCtrl, wxListCtrl)
wxEND_EVENT_TABLE()

SoftListCtrl::SoftListCtrl(wxWindow* parent, SoftScannerPtr scanner)
	: wxListCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_VIRTUAL | wxBORDER_THEME | wxLC_EDIT_LABELS)
	, scanner_(scanner)
{
	wxListItem col0;
	col0.SetId(0);
	col0.SetText(wxT("Name"));
	col0.SetWidth(100);
	InsertColumn(0, col0);

	wxListItem col1;
	col1.SetId(1);
	col1.SetText(wxT("Publisher"));
	col1.SetWidth(100);
	InsertColumn(1, col1);

	wxListItem col2;
	col2.SetId(2);
	col2.SetText(wxT("InstalledOn"));
	col2.SetWidth(100);
	InsertColumn(2, col2);

	wxListItem col3;
	col3.SetId(3);
	col3.SetText(wxT("Size"));
	col3.SetWidth(100);
	InsertColumn(3, col3);

	wxListItem col4;
	col4.SetId(4);
	col4.SetText(wxT("Version"));
	col4.SetWidth(100);
	InsertColumn(4, col4);

	wxListItem col5;
	col5.SetId(5);
	col5.SetText(wxT("Scanned by"));
	col5.SetWidth(100);
	InsertColumn(5, col5);

	wxListItem col6;
	col6.SetId(6);
	col6.SetText(wxT("Architecture"));
	col6.SetWidth(100);
	InsertColumn(6, col6);
}

SoftListCtrl::~SoftListCtrl()
{ }

wxString SoftListCtrl::OnGetItemText(long item, long column) const
{
	Software soft = scanner_->GetScanResult()->at(item);

	if (column == 0)
		return soft.name_;
	else if (column == 1)
		return soft.publisher_;
	else if (column == 2)
	{
		wxDateTime dt;
		if (!dt.ParseFormat(soft.installedOn_, wxT("%Y%m%d")))
			return wxT("");

		return dt.Format(wxT("%d.%m.%Y"));
	}
	else if (column == 3)
	{
		wxULongLong_t size;
		if (wxString(soft.size_).ToULongLong(&size))
		{
			size *= 1024;
			return wxFileName::GetHumanReadableSize(size, wxT("Size error"), 2);
		}

		return soft.size_;
	}
	else if (column == 4)
		return soft.version_;
	else if (column == 5)
		return soft.scannedBy_;
	else if (column == 6)
	{
		if (soft.arch_ == Software::x86)
			return wxT("x86");
		else if (soft.arch_ == Software::x64)
			return wxT("x64");
		else
			return wxT("Unknown");
	}

	return wxT("Unknown");
}

}
