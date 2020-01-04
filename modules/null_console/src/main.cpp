#include "pch.h"

static const wxCmdLineEntryDesc cmdLineDesc[] =
{
	{ wxCMD_LINE_SWITCH, "h", "help", "show this help message",
	wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },
	{ wxCMD_LINE_SWITCH, "d", "dummy", "a dummy switch",
	wxCMD_LINE_VAL_NONE, wxCMD_LINE_PARAM_OPTIONAL },
	{ wxCMD_LINE_NONE }
};

int _tmain(int argc, wxChar **argv)
{
	try
	{
		wxApp::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE, "null_console");

		wxInitializer initializer;
		if (!initializer)
			throw std::runtime_error("Failed to initialize the wxWidgets library, aborting.");

		wxCmdLineParser parser(cmdLineDesc, argc, argv);
		switch (parser.Parse())
		{
		case -1:
		{
			// help was given, terminating
			break;
		}
		case 0:
		{
			// everything is ok; proceed
			if (parser.Found("d"))
			{
				wxPrintf("Dummy switch was given...\n");
			}
			break;
		}
		default:
			break;
		}

		if (argc == 1)
		{
			// If there were no command-line options supplied, emit a message
			// otherwise it's not obvious that the sample ran successfully
			wxPrintf("Welcome to the wxWidgets 'console' sample!\n");
			wxPrintf("For more information, run it again with the --help option\n");
		}
	}
	catch (std::exception& e)
	{
		wxMessageBox(wxString::FromUTF8(e.what()), wxT("Error occurred"), wxICON_ERROR);
	}

	return 0;
}