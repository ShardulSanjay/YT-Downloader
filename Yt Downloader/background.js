chrome.runtime.onMessage.addListener((message) => {
    if (message.type === 'DownloadVideo') {
        console.log('Download request received in background script.');
        
        chrome.storage.local.get(['location', 'format', 'quality','audio'], (data) => {
            console.log('Using saved settings:', data);
            //Send data to the native app
            if(!data.location){
                data.location="C:\\music";
            }
            sendToNativeApp(data.location,data.format,data.quality,message.url,data.audio);
        });
        // Keep the message channel open for async operations
        return true;
    }
});

chrome.tabs.onUpdated.addListener((tabId, changeInfo) => {
    if (changeInfo.url && changeInfo.url.includes("youtube.com/watch")) {
        chrome.tabs.sendMessage(tabId, {
            type: "NEW"
        });
    }
});
function sendToNativeApp(loc,form,qual,url,audio){
    const port=chrome.runtime.connectNative("com.connection.ytdlp");
    port.postMessage({"location":loc,"format":form,"quality":qual,"url":url,"audio":audio});
    port.onMessage.addListener(function (message){
        port.disconnect();
        for(let key in message){
            console.log(`key is :${key} value:${message[key]}`);
        }
    });
    port.onDisconnect.addListener(function (){
        console.error(chrome.runtime.lastError.message);
    });
}
    



