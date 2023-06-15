#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Masukkan SSID dan Password Wi-Fi yang digunakan
const char *ssid = "DESKTOP-ZAKI";
const char *password = "88888888";

// Membuat AsyncWebServer object pada port 80
AsyncWebServer server(80);
// Membuat AsyncWebSocket pada path "/ws"
AsyncWebSocket ws("/ws");

void setup() {
  Serial.begin(115200);

  // Koneksi ke Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  // Print IP Address dari ESP32
  Serial.println(WiFi.localIP());

  // Start server dan inisiasi web socket
  server.begin();
  server.addHandler(&ws);

  // Route: "/"
  // Method: GET
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    String htmlContent = R"HTML(
      <!DOCTYPE html>
      <html lang="en">
        <head>
          <meta charset="UTF-8" />
      <meta name="viewport" content="width=device-width, initial-scale=1.0" />
      <title>Home</title>
      <script src="https://cdn.tailwindcss.com"></script>
      <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
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
          class="py-10 w-[277px] relative flex flex-col gap-10 h-screen text-white bg-gradient-purple1 flex flex-col justify-between items-center"
        >
          <img class="px-5" src="https://sbm-final-project-fe.vercel.app/Logo.png" />
          <ul class="text-[24px] w-full flex flex-col items-center relative">
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
              class="text-[24px] font-semibold bg-gradient-purple2 text-transparent bg-clip-text"
            >
              Dashboard
            </h1>
            <hr class="w-full bg-gradient-purple1 h-[4px] rounded-full" />
          </div>
          <main class="flex flex-col gap-5 py-5">
            <div class="flex gap-5">
              <div
                class="drop-shadow-1 relative bg-white px-4 py-3 overflow-hidden rounded-[20px] w-[250px]"
              >
                <h1 class="text-[20px] text-[#5740B4]">Temperature</h1>
                <h2
                  id="temperature"
                  class="text-[30px] font-bold text-transparent bg-gradient-purple2 bg-clip-text w-fit"
                >
                  33.5 °C
                </h2>
                <img
                  class="absolute top-0 right-0 h-full"
                  src="https://sbm-final-project-fe.vercel.app/temp_icon.png"
                  alt=""
                />
              </div>
              <div
                class="drop-shadow-1 bg-white px-4 py-3 relative overflow-hidden rounded-[20px] w-[250px]"
              >
                <h1 class="text-[20px] text-[#5740B4]">Humidity</h1>
                <h2
                  class="text-[30px] font-bold text-transparent bg-gradient-purple2 bg-clip-text w-fit"
                >
                  70 %
                </h2>
                <img
                  src="https://sbm-final-project-fe.vercel.app/humid_icon.png"
                  alt=""
                  class="absolute top-0 right-0 h-full"
                />
              </div>
            </div>
            <div class="flex gap-5">
              <div
                class="drop-shadow-1 bg-white px-4 py-3 relative overflow-hidden rounded-[20px] w-[550px]"
              >
                <div class="flex justify-between mb-3">
                  <h1 class="text-[20px] text-[#5740B4]">Status Chart</h1>
                  <form class="bg-gradient-purple2 p-[1px] h-fit rounded-[6px]">
                    <select
                      class="w-fit rounded-[5px] text-center text-[#5740B4]"
                    >
                      <option>Speed</option>
                      <option>Acceleration</option>
                      <option>Speed</option>
                    </select>
                  </form>
                </div>
                <div>
                  <canvas id="myChart"></canvas>
                </div>
              </div>
              <div class="drop-shadow-1 bg-white px-4 py-3 rounded-[20px]">
                <div class="flex justify-between items-end mb-3">
                  <h1 class="text-[20px] text-[#5740B4]">Car Status</h1>
                  <div class="flex items-center gap-3 bg-gradient-green1 text-transparent bg-clip-text font-bold">
                    <span
                      class="block w-[10px] h-[10px] rounded-full bg-gradient-green1"
                    ></span>
                    Monitoring
                  </div>
                </div>
                <div class="flex gap-20 mb-2">
                  <div>
                    <h1 class="text-[#828282] text-[14px] font-semibold">
                      Speed
                    </h1>
                    <h2
                      class="text-[30px] font-bold text-transparent bg-gradient-purple2 bg-clip-text w-fit"
                    >
                      6 m/s
                    </h2>
                  </div>
                  <div>
                    <h1 class="text-[#828282] text-[14px] font-semibold">
                      Distance Travelled
                    </h1>
                    <h2
                      class="text-[30px] font-bold text-transparent bg-gradient-purple2 bg-clip-text w-fit"
                    >
                      20 m
                    </h2>
                  </div>
                </div>
                <div class="flex gap-20 mb-2">
                  <div>
                    <h1 class="text-[#828282] text-[14px] font-semibold">
                      Drift (yaw)
                    </h1>
                    <h2
                      class="text-[30px] font-bold text-transparent bg-gradient-purple2 bg-clip-text w-fit"
                    >
                      5.28 °
                    </h2>
                  </div>
                  <div>
                    <h1 class="text-[#828282] text-[14px] font-semibold">
                      Drift (roll)
                    </h1>
                    <h2
                      class="text-[30px] font-bold text-transparent bg-gradient-purple2 bg-clip-text w-fit"
                    >
                      -8.28 °
                    </h2>
                  </div>
                </div>
                <div class="flex gap-20">
                  <div>
                    <h1 class="text-[#828282] text-[14px] font-semibold">
                      Drift (pitch)
                    </h1>
                    <h2
                      class="text-[30px] font-bold text-transparent bg-gradient-purple2 bg-clip-text w-fit"
                    >
                      8.29 °
                    </h2>
                  </div>
                </div>
              </div>
            </div>
          </main>
        </div>
      </main>
      </body>
      <style>
        * {
          margin: 0;
          padding: 0;
          box-sizing: border-box;
        }
        .bg-gradient-purple1 {
          background: linear-gradient(
            rgba(42, 88, 208),
            rgba(87, 64, 180),
            rgba(66, 145, 180)
          );
        }
        .bg-gradient-purple2 {
          background: linear-gradient(
            100deg,
            rgba(42, 88, 208),
            rgba(87, 64, 180),
            rgba(66, 145, 180)
          );
        }
        .bg-gradient-green1 {
          background: linear-gradient(
            #0DCC2B,
            #11AC62,
            #3E9B65
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
        .dark {
          background-color: #16181b !important;
          color:white;
        }
      </style>
      <script defer>
        const ctx = document.getElementById("myChart");
        const body = document.querySelector("body");

        if(localStorage.getItem("theme") === "dark") {
          body.classList.add("dark");
        }

        new Chart(ctx, {
          type: "line",
          data: {
            labels: ["Red", "Blue", "Yellow", "Green", "Purple", "Orange"],
            datasets: [
              {
                label: "# of Votes",
                data: [12, 19, 3, 5, 2, 3],
                borderWidth: 1,
              },
            ],
          },
          options: {
            backgroundColor: "#5740B4",
            borderWidth: 10,
            borderColor: "#5740B4D3",
            scales: {
              y: {
                beginAtZero: true,
              },
            },
          },
        });
        
        const websocket = new WebSocket("ws://192.168.137.91/ws");

        websocket.addEventListener("open", (event) => {
          websocket.send("Hello Server!");
        });

        websocket.addEventListener("message", (event) => {
          // console.log(event.data);
          const temperature = document.querySelector("#temperature");
          temperature.innerHTML = JSON.parse(event.data).temperature + " °C";
        });
        
        </script>
      </html>
      )HTML";
    request->send(200, "text/html", htmlContent);
  });

  // Route: "/about"
  // Method: GET
  server.on("/about", HTTP_GET, [](AsyncWebServerRequest *request) {
    String htmlContent = R"HTML(
      <!DOCTYPE html>
      <html lang="en">
        <head>
          <meta charset="UTF-8" />
          <meta name="viewport" content="width=device-width, initial-scale=1.0" />
          <title>Home</title>
          <script src="https://cdn.tailwindcss.com"></script>
          <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
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
              class="py-10 w-[277px] flex flex-col gap-10 h-screen text-white bg-gradient-purple1 flex flex-col justify-between items-center"
            >
              <h1 class="underline underline-offset-4 underline-white text-[24px]">
                Project SBM
              </h1>
              <ul class="text-[24px] relative w-full flex flex-col items-center">
                <div
                  class="absolute right-0 top-0 bg-[#F5F5F5] w-[95%] h-[25%] rounded-l-full translate-y-[300%]"
                ></div>
                <li class="py-3 z-[2]">
                  <a href="/">Home</a>
                </li>
                <li class="py-3 z-[2]">
                  <a href="/history">History</a>
                </li>
                <li class="py-3 z-[2]">
                  <a href="/settings">Settings</a>
                </li>
                <li class="py-3 z-[2] font-semibold !text-[#5740B4]">
                  <a href="/about">About</a>
                </li>
              </ul>
              <p class="text-[18px]">&copy; 2023</p>
            </aside>
            <div class="p-10 w-full">
              <div class="flex items-center gap-5">
                <h1
                  class="text-[24px] font-semibold bg-gradient-purple2 text-transparent bg-clip-text"
                >
                  About
                </h1>
                <hr class="w-full bg-gradient-purple2 h-[4px] rounded-full" />
              </div>
              <main class="py-5">
                <h1 class="text-[#5740B4] text-[22px] font-bold underline underline-[#5740B4]">Our Team:</h1>
                <ul class="text-[#5740B4]">
                  <li class="w-fit">
                    <a
                      class="w-fit block hover:underline underline-[#5740B4]"
                      href="https://github.com/NandoAACF"
                    >
                      <h1 class="font-semibold">
                        Agustinus Angelo Christian Fernando
                      </h1>
                    </a>
                    <h2>21/473804/TK/52235</h2>
                  </li>
                  <li class="w-fit">
                    <a
                      class="w-fit block font-semibold hover:underline underline-[#5740B4]"
                      href="https://github.com/ahmadzaki2975"
                    >
                      <h1>Ahmad Zaki Akmal</h1>
                    </a>
                    <h2>21/480179/TK/52981</h2>
                  </li>
                  <li class="w-fit">
                    <a
                      class="w-fit block hover:underline underline-[#5740B4] font-semibold"
                      href="https://github.com/aufarhmn"
                    >
                      <h1>Aufa Nasywa Rahman</h1>
                    </a>
                    <h2>21/475255/TK/52454</h2>
                  </li>
                  <li class="w-fit">
                    <a
                      class="w-fit block hover:underline underline-[#5740B4] font-semibold"
                      href="https://github.com/DiftaFitrahul"
                    >
                      <h1>Difta Fitrahul Qihaj</h1>
                    </a>
                    <h2>21/480096/TK/52975</h2>
                  </li>
                  <li class="w-fit">
                    <a
                      class="w-fit block hover:underline underline-[#5740B4] font-semibold"
                      href="https://github.com/gigahidjrikaaa"
                    >
                      <h1>Giga Hidjrika Aura Adkhy</h1>
                    </a>
                    <h2>21/479228/TK/52833</h2>
                  </li>
                </ul>
                <h1 class="text-[#5740B4] text-[22px] font-bold underline underline-[#5740B4] mt-5">Quick Links:</h1>
                <a
                  class="text-[#5740B4] hover:underline undelrine-[#5740B4] font-semibold"
                  href="https://github.com/ahmadzaki2975/Chem-E-Car-Monitoring"
                >
                  Main Repository
                </a>
                <p>
                  The repository containing the code for the ESP32
                </p>
                <a
                  class="text-[#5740B4] hover:underline undelrine-[#5740B4] font-semibold"
                  href="https://github.com/ahmadzaki2975/SBM-Final-Project-HTML"
                >
                  HTML Dev Repository
                </a>
                <p>
                  The repository containing the code for the HTML during development phase.
                </p>
              </main>
            </div>
          </main>
        </body>
        <style>
          * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
          }
          .bg-gradient-purple1 {
            background: linear-gradient(
              rgba(42, 88, 208),
              rgba(87, 64, 180),
              rgba(66, 145, 180)
            );
          }
          .bg-gradient-purple2 {
            background: linear-gradient(
              100deg,
              rgba(42, 88, 208),
              rgba(87, 64, 180),
              rgba(66, 145, 180)
            );
          }
          .bg-gradient-green1 {
            background: linear-gradient(#0dcc2b, #11ac62, #3e9b65);
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
        <script defer>
          const ctx = document.getElementById("myChart");

          new Chart(ctx, {
            type: "line",
            data: {
              labels: ["Red", "Blue", "Yellow", "Green", "Purple", "Orange"],
              datasets: [
                {
                  label: "# of Votes",
                  data: [12, 19, 3, 5, 2, 3],
                  borderWidth: 1,
                },
              ],
            },
            options: {
              backgroundColor: "#5740B4",
              borderWidth: 10,
              borderColor: "#5740B4D3",
              scales: {
                y: {
                  beginAtZero: true,
                },
              },
            },
          });
        </script>
      </html>)HTML";
    request->send(200, "text/html", htmlContent);
  });
}

void loop() {
  ws.cleanupClients();

  // Test random data
  int temp = random(0, 100);

  // Constructing JSON
  String jsonString = "";
  jsonString += "{";
  jsonString += "\"temperature\" : ";
  jsonString += temp;
  jsonString += "}";

  // Sending JSON using websocket
  ws.textAll(jsonString);
  Serial.println(jsonString);
  delay(500);
}
