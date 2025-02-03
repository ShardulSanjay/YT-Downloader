# YouTube Downloader Chrome Extension

A simple Chrome extension to download MP3 OR MP4 videos from YouTube directly with customized quality settings for videos and audio using YT-DLP.

## Features

- Download videos and audio files directly from youtube in a single click. 
- Choose the desired audio bitrate (e.g., 320kbps,128kbps, 192kbps, 320kbps) and video quality(e.g., 720p,1080p).
- Convert the audio to MP3 format if it is not already in that format.
- Download MP4 files as per specified resolution and then use AVC format for video stream and AAC format for audio stream.

## Requirements

- Ensure Windows defender is on the latest version, guide:https://www.youtube.com/watch?v=oazzLAprlI0
- This extension is for WINDOWS only, it will not run on Mac or linux.

## How to Use

1. **Install the Extension**:
   - Install Latest Version of Python which can be found here (ignore if already installed): https://www.python.org/downloads/
   - Install yt-dlp and ffmpeg, installation guide for yt-dlp and ffmpeg can be found here(ignore if already installed): https://www.spacebar.news/how-to-install-yt-dlp/
   - Download the extension files by going to code>download zip.
   - Cut the 'native-cpp-connection-script' and paste it in your c drive.
   - Cut the 'Yt Downloader' file and paste it in your desktop.
   - Open Chrome and go to `chrome://extensions/`.
   - Enable **Developer mode**.
   - Click on **Load unpacked** and select the 'YT Downloader' folder on your desktop.
   - In your search bar search for registry editor,navigate to 'Computer\HKEY_CURRENT_USER\Software\Google\Chrome\NativeMessagingHosts\' right click on the file and add new>key,
     enter the name of the key as:-'com.connection.ytdlp', now on the right side click on (default) and enter the path to your manifest.json file from the native-cpp-connection-script folder,
     it should look like this-'C:\native-cpp-connection-script\manifest.json' enter it into Value data:.
   - Open the manifest.json file located in C:\native-cpp-connection-script\manifest.json using Notepad and ensure that the "allowed_origins" field contains your extension's correct ID. The ID
     can be found on the chrome://extensions/ page. Since the ID varies for each pc, update the manifest accordingly. It should be formatted as follows:
     "allowed_origins": ["chrome-extension://your-extension-id/"]
     For example, if your extension ID is kngnhogaplkemaannfbedggibcboakjb, the entry would be:
     "allowed_origins": ["chrome-extension://kngnhogaplkemaannfbedggibcboakjb/"]
     Once you've updated the file, save the changes(Important). 

2. **Using the Extension**:
   - Click on the extension icon in your Chrome toolbar and pin it.
   - Paste the path to your download folder in the first field (example: C:\Users\SAM\Desktop\music (Do not copy this as the path will be different for your computer))
     and ensure a valid file exists at that location. If an invalid location is entered no file will be downloaded, if no location has been entered the file will be downloaded to "C:\music"
   - Choose the desired audio quality (bitrate) (e.g., 192kbps).
   - Choose the desired video quality  (e.g., 720p).
   - Click the **Download** button on your youtube player, this will be located on the right of the volume setting on youtube or to the left of the autoplay button.
     Clicking the button will download the file to the specified folder automatically using the saved settings.

3. **Customizing Audio Quality**:
   - The extension supports audio quality settings (e.g., 128kbps, 192kbps, 320kbps).
   - The `audio-quality` setting will adjust the downloaded audio to the specified bitrate, and the extension will fetch the best available audio stream to minimize file size while ensuring quality.

3. **Customizing Video Quality**:
   - The extension supports video quality settings (e.g., 720p, 1080p, 4k).
   - The `video-quality` setting will adjust the downloaded video to the specified quality, and the extension will fetch the best available video stream to minimize file size while ensuring quality.

## Supported Formats

- MP3: The extension automatically converts audio to MP3 if the original audio format is not MP3.
- Other formats (AAC, Opus) will be converted to MP3 with the specified bitrate for format MP3.
- MP4: The extension downloads AVC format for video stream and AAC format for audio stream and converts it into MP4.



