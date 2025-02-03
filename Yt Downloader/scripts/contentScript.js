console.log("contentScript.js loaded");

// Function to add the download button
function addButton() {
    const topRow = document.getElementsByClassName('ytp-left-controls')[0]; 
    
    // Check if the button already exists and the ytp controls are loaded
    if (topRow && !document.getElementById('DownloadButton')) {
        const DownloadBtn = document.createElement('button');
        DownloadBtn.id = 'DownloadButton';
        DownloadBtn.innerHTML = `<img src="${chrome.runtime.getURL('apps.png')}" style="background-color: transparent;" alt="Download">`;
        // Add the click event listener for downloads
        DownloadBtn.addEventListener('click', function () {
            chrome.runtime.sendMessage({
                type: 'DownloadVideo',
                url: window.location.href
            }, function (response) {
                console.log('Response from background script:', response);
            });
        });

        topRow.appendChild(DownloadBtn);
        console.log("Download button added after top-row");
    }
}
addButton();//invoke function when the script runs initially
// Message listener for the "NEW" message from the background script
chrome.runtime.onMessage.addListener((message) => {
    if (message.type === "NEW") {
        console.log("NEW message received, trying to add the button.");
        setTimeout(addButton, 1000);  // Slight delay for dynamic loading
    }
});
// Add the button when the page loads for the first time
window.addEventListener('load', () => {
    setTimeout(addButton, 1000);  
});





