#ifndef INDEX_PAGE_H_
#define INDEX_PAGE_H_

String IPAddress = "";

void assignIP(String IPArg) {
  IPAddress = IPArg;
}

String indexPage = R"HTML(
  <!DOCTYPE html>
<html class="overflow-x-hidden" lang="en">
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
        class="fixed top-0 flex-shrink-0 py-10 w-[277px] flex flex-col gap-10 h-screen text-white bg-gradient-purple1 flex flex-col justify-between items-center"
      >
        <img
          class="px-5"
          src="https://sbm-final-project-fe.vercel.app/Logo.png"
        />
        <ul class="text-[24px] w-full flex flex-col items-center relative">
          <div
            class="absolute right-0 top-0 bg-[#F5F5F5] w-[95%] h-[25%] rounded-l-full"
          ></div>
          <li class="py-3 z-[2] font-semibold !text-[#5740B4]">
            <a href="/" class="flex items-center gap-3">
              <img
                class="h-[28px] mt-[-3px]"
                src="https://sbm-final-project-fe.vercel.app/HomeActive.png"
              />
              Home
            </a>
          </li>
          <li class="py-3 z-[2]">
            <a class="flex gap-3 items-center" href="/history">
              <img
                class="h-[28px]"
                src="https://sbm-final-project-fe.vercel.app/History.png"
              />
              History
            </a>
          </li>
          <li class="py-3 z-[2]">
            <a class="flex items-center gap-3" href="/settings">
              <img
                class="w-[30px]"
                src="https://sbm-final-project-fe.vercel.app/Settings.png"
              />
              Settings</a
            >
          </li>
          <li class="py-3 z-[2]">
            <a class="flex items-center gap-3" href="/about">
              <img
                class="w-[30px]"
                src="https://sbm-final-project-fe.vercel.app/About.png"
              />
              About
            </a>
          </li>
        </ul>
        <p class="text-[18px]">&copy; 2023</p>
      </aside>
      <div class="p-10 w-full !ml-[277px]">
        <div class="flex items-center gap-5">
          <h1
            class="text-[24px] font-semibold bg-gradient-purple2 text-transparent bg-clip-text"
          >
            Dashboard
          </h1>
          <hr class="w-full bg-gradient-purple1 h-[4px] rounded-full" />
        </div>
        <main class="flex flex-col gap-5 py-5">
          <div class="flex flex-col lg:flex-row gap-5">
            <div
              class="drop-shadow-1 relative bg-white px-4 py-3 overflow-hidden rounded-[20px] w-[250px] container"
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
              class="drop-shadow-1 bg-white px-4 py-3 relative overflow-hidden rounded-[20px] w-[250px] container"
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
          <div class="flex gap-5 flex-col lg:flex-row">
            <div
              class="drop-shadow-1 bg-white px-4 py-3 relative overflow-hidden rounded-[20px] w-[550px] container"
            >
              <div class="flex justify-between mb-3 w-full lg:w-1/2 flex-shrink-0">
                <h1 class="text-[20px] text-[#5740B4]">Status Chart</h1>
              </div>
              <div>
                <canvas id="myChart"></canvas>
              </div>
            </div>
            <div
              class="drop-shadow-1 bg-white px-4 py-3 rounded-[20px] container w-fit"
            >
              <div class="flex justify-between items-end mb-3">
                <h1 class="text-[20px] text-[#5740B4]">Car Status</h1>
                <div
                  class="flex items-center gap-3 bg-gradient-green1 text-transparent bg-clip-text font-bold"
                >
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
    .dark {
      background-color: #16181b !important;
      color: white;
    }
    .container-dark {
      background-color: #0f0f0f;
      color: #b77bef !important;
      filter: drop-shadow(0px 0px 5px rgba(42, 88, 208));
    }
    .text-dark {
      color: rgba(42, 88, 208) !important;
    }
  </style>
  <script defer>
    const ctx = document.getElementById("myChart");
    const body = document.querySelector("body");
    const espIP = window.location.host;
    console.log(espIP);

    if (localStorage.getItem("theme") === "dark") {
      body.classList.add("dark");
      document.querySelectorAll(".container").forEach((container) => {
        container.classList.add("container-dark");
      });
    }

    const data = [];
    const labels = [];
    const chart = new Chart(ctx, {
      type: "line",
      data: {
        labels: labels,
        datasets: [
          {
            label: "# of Votes",
            data: data,
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

    setInterval(() => {
      const random = Math.floor(Math.random() * 100);
      if (data.length > 10) {
        data.shift();
        labels.shift();
      }
      data.push(random);
      const now = new Date();
      labels.push(
        `${now.getHours() < 10 ? "0" + now.getHours() : now.getHours()}:${
          now.getMinutes() < 10 ? "0" + now.getMinutes() : now.getMinutes()
        }:${now.getSeconds() < 10 ? "0" + now.getSeconds() : now.getSeconds()}`
      );
      chart.data.datasets[0].data = data;
      chart.data.labels = labels;
      chart.update();
    }, 1000);

    const websocket = new WebSocket(`ws://${espIP}/ws`);
    websocket.addEventListener("open", (event) => {
      websocket.send("Hello Server!");
    });

    websocket.addEventListener("message", (event) => {
      const temperature = document.querySelector("#temperature");
      temperature.innerHTML = JSON.parse(event.data).temperature + " °C";
    });
  </script>
</html>
)HTML";


#endif