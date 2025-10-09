// 1. Paste the very long Base64 string you copied here.
const base64Image: string = "data:image/jpeg;base64,/9j/4AAQSkZJRgABAQEAYABgAAD..."; // <-- PASTE YOUR STRING HERE

// 2. Get references to the HTML elements using their IDs.
const imageElement = document.getElementById('processed-frame') as HTMLImageElement;
const statsElement = document.getElementById('stats') as HTMLDivElement;

// 3. Update the image source to display the sample frame.
if (imageElement) {
    imageElement.src = base64Image;
}

// 4. Update the stats div with some sample text overlays. [cite: 39]
if (statsElement) {
    const resolution = "720x1280"; // Dummy value
    const fps = "15"; // Dummy value
    statsElement.innerHTML = `<p><strong>Resolution:</strong> ${resolution} | <strong>FPS:</strong> ${fps}</p>`;
}