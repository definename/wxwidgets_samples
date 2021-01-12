#include "pch.h"
#include "GreedyFramePanel.h"
#include "GreedyTypes.h"

namespace greedy
{

class GreedyGrid : public wxGrid {
	// Public interface
public:
	GreedyGrid(wxWindow* parent)
		: wxGrid(parent, wxID_ANY)
		, values_{
			{3, 5, 4, 0, 140},
			{2, 4, 6, 0, 200},
			{1, 3, 5, 0, 180},
			{3, 6, 7, 0, 220},
			{12, 14, 16},
		}
		, lables_{ wxT("Фрезерне"), wxT("Токарне"), wxT("Зварювальне"), wxT("Шліфувальне"), wxT("Прибуток") }
	{
		CreateGrid(5, 5);

		int sum_last_col = 0;
		for (int i = 0; i < values_.size() - 1; ++i) {
			sum_last_col += values_[i][values_[i].size() - 1];
		}

		int sum_last_row = 0;
		for (int i = 0; i < values_[values_.size() - 1].size(); ++i) {
			sum_last_row += values_[values_.size() - 1][i];
		}
		values_[values_.size() - 1].push_back(sum_last_col - sum_last_row);

		for (int i = 0; i < GetNumberCols(); ++i) {
			SetCellBackgroundColour(GetNumberRows() - 1, i, wxColour(220, 220, 220));
		}
		SetColLabelValue(GetNumberCols() - 1, wxT("Загальний фонд робочого часу обладнання"));
		for (int i = 0; i < GetNumberRows(); ++i) {
			SetRowLabelValue(i, lables_.at(i));
			SetCellBackgroundColour(i, GetNumberCols() - 1, wxColour(220, 220, 220));
		}
		for (int i = 0; i < values_.size(); ++i) {
			for (int j = 0; j < values_[i].size(); ++j) {
				if (i < values_.size() - 1 && j < values_[i].size() - 1) {
					SetCellValue(i, j, wxString::Format("x%d%d (%d)", i, j, values_[i][j]));
				}
				else {
					SetCellValue(i, j, wxString::Format("%d", values_[i][j]));
				}
			}
		}
		AutoSizeColumns(true);
		AutoSizeRows(true);
		Fit();
	}

	void OnSize(wxSizeEvent& e) {
		wxSize size = GetClientSize();

		int width1 = GetRowLabelSize();
		int width2 = GetColSize(GetNumberCols() - 1);
		int width = size.GetWidth() - width1 - width2;

		width /= GetNumberCols() - 1;
		if (width > 0) {
			for (int i = 0; i < GetNumberCols() - 1; ++i) {
				SetColSize(i, abs(width));
			}
		}
	}

	wxDECLARE_EVENT_TABLE();

private:
	std::vector<std::vector<int>> values_;
	std::vector<wxString> lables_;
};

wxBEGIN_EVENT_TABLE(GreedyGrid, wxGrid)
	EVT_SIZE(GreedyGrid::OnSize)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(GreedyFramePanel, wxPanel)
	EVT_BUTTON(wxID_ANY, GreedyFramePanel::OnControl)
wxEND_EVENT_TABLE()

GreedyFramePanel::GreedyFramePanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, parent->GetSize())
{

	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	const int borderSize = 2;

	// Grid.
	wxBoxSizer* gridSizer = new wxBoxSizer(wxHORIZONTAL);
	grid_ = new GreedyGrid(this);
	gridSizer->Add(grid_, 1, wxEXPAND);
	topSizer->Add(gridSizer, 1, wxEXPAND);

	// Buttons.
	wxBoxSizer* controlSizer = new wxBoxSizer(wxVERTICAL);
	controlSizer->Add(new wxButton(this, GreedyEvent::ID_NEXT, wxT("Next")), 1, wxEXPAND);
	topSizer->Add(controlSizer, 0, wxSTRETCH_NOT, borderSize);

	SetSizer(topSizer);
}

void GreedyFramePanel::OnControl(wxCommandEvent& e) {
	const GreedyEvent buttonId = static_cast<GreedyEvent>(e.GetId());

	if (buttonId == GreedyEvent::ID_NEXT) {
		wxMessageBox(wxT("1"));
	}
}

} // namespace greedy
