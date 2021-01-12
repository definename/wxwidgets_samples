#include "pch.h"
#include "GreedyFramePanel.h"
#include "GreedyTypes.h"

namespace greedy
{

class GreedyGrid : public wxGrid {
public:
	GreedyGrid(wxWindow* parent)
		: wxGrid(parent, wxID_ANY)
		, values_{
			{2, 4, 5, 0, 140},
			{1, 8, 6, 0, 280},
			{7, 4, 5, 0, 240},
			{4, 6, 7, 0, 360},
			{10, 14, 12},
	}
	, lables_{ wxT("Борошно-змішувальне"), wxT("Дозаторне"), wxT("Тістоформуюче"), wxT("Хлібопекарське"), wxT("Прибуток") }
	{
		CreateGrid(5, 5);
		SetLabelBackgroundColour(wxColour(255, 153, 255));
		wxColour label_color = wxColour(255, 255, 102);

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
			SetCellBackgroundColour(GetNumberRows() - 1, i, label_color);
		}
		SetColLabelValue(GetNumberCols() - 1, wxT("Загальний фонд робочого часу обладнання"));
		for (int i = 0; i < GetNumberRows(); ++i) {
			SetRowLabelValue(i, lables_.at(i));
			SetCellBackgroundColour(i, GetNumberCols() - 1, label_color);
		}

		for (int i = 0; i < values_.size(); ++i) {
			for (int j = 0; j < values_[i].size(); ++j) {
				auto val = values_[i][j];
				if (i < values_.size() - 1 && j < values_[i].size() - 1) {
					SetCellValue(i, j, wxString::Format("X%d%d (%d)", i, j, val));
					list_values_.push_back(val);
				}
				else {
					SetCellValue(i, j, wxString::Format("%d", val));
				}
			}
		}
		std::sort(list_values_.begin(), list_values_.end(), std::greater<int>());
		for (int i = 0; i < values_.size() - 1; ++i) {
			list_last_col_.push_back(values_[i][values_[i].size() - 1]);
		}
		for (int i = 0; i < values_.size(); ++i) {
			if (i == values_.size() - 1) {
				for (int j = 0; j < values_[i].size(); ++j) {
					list_last_row_.push_back(values_[i][j]);
				}
			}
		}

		SetRowLabelSize(150);
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

	void DoNext() {
		wxColour select_color = wxColour(0, 255, 204);
		static bool released = false;
		if (list_values_.empty()) {
			if (!released) {
				for (int i = 0; i < values_.size() - 1; ++i) {
					for (int j = 0; j < values_[i].size() - 1; ++j) {
						int val = values_[i][j];
						if (val == 0) {
							int col_value = list_last_col_[i];
							SetCellBackgroundColour(i, j, select_color);
							SetCellValue(i, j, wxString::Format("%d(%d)", col_value, val));
						}
					}
				}
				released = true;
			}
			else {
				wxMessageBox(wxT("Done!"));
			}
			return;
		}

		while (list_values_.back() == 0) {
			list_values_.pop_back();
		}
		int v = list_values_.back();
		list_values_.pop_back();
		for (int i = 0; i < values_.size() - 1; ++i) {
			for (int j = 0; j < values_[i].size() - 1; ++j) {
				int val = values_[i][j];
				if (val == v) {
					int row_value = list_last_row_[j];
					int col_value = list_last_col_[i];
					SetCellBackgroundColour(i, j, select_color);
					if (row_value > col_value) {
						SetCellValue(i, j, wxString::Format("%d(%d)", col_value, val));
						list_last_col_[i] = 0;
						list_last_row_[j] -= col_value;
					}
					else if (col_value > row_value) {
						SetCellValue(i, j, wxString::Format("%d(%d)", row_value, val));
						list_last_col_[i] -= row_value;
						list_last_row_[j]  = 0;
					}
					else if (col_value == row_value) {
						SetCellValue(i, j, wxString::Format("%d(%d)", row_value, val));
						list_last_col_[i] = 0;
						list_last_row_[j] = 0;
					}
				}
			}
		}
		while (!list_values_.empty() && v == list_values_.back()) {
			list_values_.pop_back();
		}
		Refresh();
	}

	wxDECLARE_EVENT_TABLE();

private:
	std::vector<std::vector<int>> values_;
	std::vector<wxString> lables_;
	std::vector<int> list_values_;
	std::vector<int> list_last_row_;
	std::vector<int> list_last_col_;
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

	// Buttons.
	wxBoxSizer* controlSizer = new wxBoxSizer(wxVERTICAL);
	controlSizer->Add(new wxButton(this, GreedyEvent::ID_NEXT, wxT("Next")), 1, wxEXPAND);
	topSizer->Add(controlSizer, 0, wxSTRETCH_NOT, borderSize);

	// Grid.
	wxBoxSizer* gridSizer = new wxBoxSizer(wxHORIZONTAL);
	grid_ = new GreedyGrid(this);
	gridSizer->Add(grid_, 1, wxEXPAND);
	topSizer->Add(gridSizer, 1, wxEXPAND);

	SetSizer(topSizer);
}

void GreedyFramePanel::OnControl(wxCommandEvent& e) {
	const GreedyEvent buttonId = static_cast<GreedyEvent>(e.GetId());

	if (buttonId == GreedyEvent::ID_NEXT) {
		grid_->DoNext();
	}
}

} // namespace greedy
