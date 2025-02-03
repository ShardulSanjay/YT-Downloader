#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#undef UNICODE//don't use unicode
#undef _UNICODE
#include <windows.h>
using std::string;
using json = nlohmann::json;

void sendMessage(string message){
    unsigned int len = message.length();//Send the amount of bytes of the json message to chrome
    printf("%c%c%c%c",  
        (char) (len & 0xff),           // least significant byte
        (char) ((len >> 8) & 0xff),    // 2nd byte
        (char) ((len >> 16) & 0xff),   // 3rd byte
        (char) ((len >> 24) & 0xff));  // most significant byte
    
    printf("%s", message.c_str());//send the json formatted string to chrome
}
void handleDownload(const nlohmann::json &jsonData) {    
    if (jsonData.contains("location") && jsonData.contains("format") &&
        jsonData.contains("quality") && jsonData.contains("url")&& jsonData.contains("audio")) {
        string loc = jsonData["location"];
        string format = jsonData["format"];
        string quality = jsonData["quality"];
        string ur = jsonData["url"];
        string url="";
        string audio=jsonData["audio"];
        for(char c:ur){//Don't add the playlist info in the url
            if(c=='&'){
                break;
            }
            url+=c;
        }
        if (!loc.empty() && loc.back() != '\\') {//append \ to the location to put the file in the download location
            loc += '\\';
        }
        // Construct the yt-dlp command
        string command="";
        if (format == "mp3") {//download the best audio with better bitrate than the one selected and then convert it to the selected quality
            command = "yt-dlp -f \"bestaudio[abr>"+audio+"]/best[abr>"+audio+"]/ba/b\" --extract-audio --audio-format mp3 --audio-quality " + audio + " -o \"" + loc + "%(title)s.%(ext)s\" " + url;
        }
        else{//download the video file with the selected resolution with vcodec avc and audio codec aac
            //command = "yt-dlp -f \"bestvideo[height<=" + quality + "]+bestaudio/best[height<=" + quality + "]\" --merge-output-format mp4 -o \"" + loc + "%(title)s.%(ext)s\" " + url;
            //command = "yt-dlp -f \"bestvideo[height<=" + quality + "]+bestaudio[ext=mp3]/best[ext=mp3]/ bv*+ba/b\" -o \"" + loc + "%(title)s.%(ext)s\" " + url;
            command = "yt-dlp -S \"res:"+quality+" \" -f \"bv*[vcodec^=avc1]+ba[acodec^=mp4a]/b[ext=mp4]\" --postprocessor-args \"-c:v copy -c:a aac -b:a 192k\" --merge-output-format mp4 -o \"" + loc + " %(title)s.%(ext)s\" " + url;

        }         
        command += " --no-progress --quiet --no-warnings";//tell yt-dlp to not print anything to stdout stream since this is not expected by chrome and leads to errors
        // Execute the command
        char COMMAND[command.length() + 1]; 
	    strcpy(COMMAND, command.c_str()); 
        STARTUPINFO si;
        si.dwFlags |= STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_SHOW; // or SW_HIDE to keep it hidden
        PROCESS_INFORMATION pi;

        ZeroMemory( &si, sizeof(si) );
        si.cb = sizeof(si);
        ZeroMemory( &pi, sizeof(pi) );
        // Start the child process. 
        if( !CreateProcess( NULL,   // No module name (use command line)
            COMMAND,        // Command line
            NULL,           // Process handle not inheritable
            NULL,           // Thread handle not inheritable
            FALSE,          // Set handle inheritance to FALSE
            0,              // No creation flags
            NULL,           // Use parent's environment block
            NULL,           // Use parent's starting directory 
            &si,            // Pointer to STARTUPINFO structure
            &pi )           // Pointer to PROCESS_INFORMATION structure
        ) 
        {
            DWORD error=GetLastError();
            sendMessage("{\"result\":\" Error in CreateProcess() code:" + std::to_string(error) + "\"}");
            return;
        }

        // Wait until child process exits.
        WaitForSingleObject( pi.hProcess, INFINITE );

        // Close process and thread handles. 
        CloseHandle( pi.hProcess );
        CloseHandle( pi.hThread );
    }    
}    

int main()
{
    unsigned int length = 0;
    for (int index = 0; index < 4; index++)
    {
        unsigned int read_char = getchar();
        length = length | (read_char << (index * 8));  // Keep shifting in the right order
    }
    std::string message = "";
    for (int index = 0; index < length; index++)
    {
        message += getchar();
    }   
    
    try {
        json parsedJson = json::parse(message);
        handleDownload(parsedJson); // Pass the parsed JSON to the handler function
    }        
    catch (...) {
        sendMessage("{\"result\":\"Download failed! Error in JSON parsing\"}");
    }    
}
