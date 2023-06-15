#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "Obscurian";
const char* password = "88888888";

WebServer server(80);

void handleRoot() {
  // Send HTTP response
  const char* homePage = R"HTML(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Home</title>
    <script src="https://cdn.tailwindcss.com"></script>
    <link rel="preconnect" href="https://fonts.googleapis.com" />
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin />
    <link
      href="https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700&display=swap"
      rel="stylesheet"
    />
  </head>
  <body class="bg-[#F5F5F5]">
    <main class="font-inter flex">
      <aside
        class="py-10 w-[277px] flex flex-col gap-10 h-screen text-white bg-gradient-1 flex flex-col justify-between items-center"
      >
        <h1 class="underline underline-offset-4 underline-white text-[24px]">
          Project SBM
        </h1>
        <ul class="text-[24px] relative w-full flex flex-col items-center">
          <div
            class="absolute right-0 top-0 bg-[#F5F5F5] w-[95%] h-[25%] rounded-l-full"
          ></div>
          <li class="py-3 z-[2] font-semibold !text-[#5740B4]">
            <a href="/">Home</a>
          </li>
          <li class="py-3 z-[2]">
            <a href="/history">History</a>
          </li>
          <li class="py-3 z-[2]">
            <a href="/settings">Settings</a>
          </li>
          <li class="py-3 z-[2]">
            <a href="/about">About</a>
          </li>
        </ul>
        <p class="text-[18px]">&copy; 2023</p>
      </aside>
      <div class="p-10 w-full">
        <div class="flex items-center gap-5">
          <h1
            class="text-[24px] font-semibold bg-gradient-1 text-transparent bg-clip-text"
          >
            Dashboard
          </h1>
          <hr class="w-full bg-gradient-1 h-[4px] rounded-full" />
        </div>
        <main class="flex flex-col gap-5 py-5">
          <div class="flex gap-5">
            <div class="drop-shadow-1 relative bg-white px-4 py-3 overflow-hidden rounded-[20px] w-[250px]">
              <h1 class="text-[20px] text-[#5740B4]">Temperature</h1>
              <h2 class="text-[30px] font-bold text-[#5740B4]">33.5 C</h2>
              <img class="absolute top-0 right-0 h-full" src="https://sbm-final-project-fe.vercel.app/temp_icon.png" alt="" />
            </div>
            <div class="drop-shadow-1 bg-white px-4 py-3 relative overflow-hidden rounded-[20px] w-[250px]">
              <h1 class="text-[20px] text-[#5740B4]">Humidity</h1>
              <h2 class="text-[30px] font-bold text-[#5740B4]">70 %</h2>
              <img src="https://sbm-final-project-fe.vercel.app/humid_icon.png" alt="" class="absolute top-0 right-0 h-full" />
            </div>
          </div>
          <div class="drop-shadow-1 bg-white px-4 py-3 relative overflow-hidden rounded-[20px] w-[550px] h-[200px]">
            <h1 class="text-[20px] text-[#5740B4]">Chart</h1>
          </div>
        </main>
      </div>
    </main>
  </body>
  <style>
    .bg-gradient-1 {
      background: linear-gradient(
        rgba(42, 88, 208),
        rgba(87, 64, 180),
        rgba(66, 145, 180)
      );
    }
    .font-inter {
      font-family: "Inter", sans-serif;
    }
    .bg-clip-text {
      -webkit-background-clip: text;
      background-clip: text;
    }
    .drop-shadow-1 {
      filter: drop-shadow(5px 12px 10px rgba(0, 0, 0, 0.3));
    }
  </style>
</html>
)HTML";
  server.send(200, "text/html", homePage);
}

void setup() {
  // Initialize serial for debugging
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Print ESP32 local IP address
  Serial.println(WiFi.localIP());

  // Route for root URL
  server.on("/", handleRoot);

  // Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  // Handle client requests
  server.handleClient();
}
