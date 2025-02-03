// Wait for the document to fully load before attaching event listeners
document.addEventListener('DOMContentLoaded', function () {
    loadSavedSettings();

    // Add event listeners to the form elements to save changes to local storage
    document.getElementById('location').addEventListener('input', saveSettings);
    document.querySelectorAll('input[name="format"]').forEach(input => {
        input.addEventListener('change', saveSettings); // for radio buttons
    });
    document.querySelectorAll('input[name="quality"]').forEach(input => {
        input.addEventListener('change', saveSettings); // for radio buttons
    });
    document.querySelectorAll('input[name="audio"]').forEach(input => {
        input.addEventListener('change', saveSettings); // for radio buttons
    });
});

// Load saved settings from local storage (if any)
function loadSavedSettings() {
    chrome.storage.local.get(['location', 'format', 'quality','audio'], function (data) {
        if (data.location) {
            document.getElementById('location').value = data.location;
        }
        if (data.format) {
            document.querySelector(`input[name="format"][value="${data.format}"]`).checked = true;
        }
        if (data.quality) {
            document.querySelector(`input[name="quality"][value="${data.quality}"]`).checked = true;
        }
        if (data.audio) {
            document.querySelector(`input[name="audio"][value="${data.audio}"]`).checked = true;
        }
    });
}

// Save settings to local storage
function saveSettings() {
    const location = document.getElementById('location').value;
    const format = document.querySelector('input[name="format"]:checked')?.value || "mp4";
    const quality = document.querySelector('input[name="quality"]:checked')?.value || "1080";
    const audio = document.querySelector('input[name="audio"]:checked')?.value || "0";
    chrome.storage.local.set({
        location: location,
        format: format,
        quality: quality,
        audio: audio
    }, function () {
        console.log('Settings saved locally.');
    });
}





