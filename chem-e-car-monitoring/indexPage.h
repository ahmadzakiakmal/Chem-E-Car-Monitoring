#ifndef INDEX_PAGE_H_
#define INDEX_PAGE_H_

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
            id="active-indicator"
            class="absolute right-0 top-0 bg-[#F5F5F5] w-[95%] h-[33%] rounded-l-full"
          ></div>
          <li
            class="py-3 z-[2] font-semibold text-transparent bg-gradient-purple2 bg-clip-text"
          >
            <a href="/" class="flex items-center gap-3">
              <img
                class="h-[28px] mt-[-3px]"
                src="https://sbm-final-project-fe.vercel.app/HomeActive.png"
              />
              Home
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
          <div class="w-full bg-gradient-purple2 h-[4px] rounded-full"></div>
        </div>
        <main class="flex flex-col gap-5 py-5">
          <div class="flex flex-col lg:flex-row gap-5">
            <div
              class="drop-shadow-1 relative bg-white px-4 py-3 overflow-hidden rounded-[20px] w-[250px] container"
            >
              <h1
                class="text-[20px] text-transparent bg-gradient-purple2 bg-clip-text font-semibold"
              >
                Temperature
              </h1>
              <h2
                id="temperature"
                class="text-[30px] font-bold text-transparent bg-gradient-purple2 bg-clip-text w-full"
              >
                0 °C
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
              <h1
                class="text-[20px] text-transparent bg-gradient-purple2 bg-clip-text font-semibold"
              >
                Humidity
              </h1>
              <h2
                id="humidity"
                class="text-[30px] font-bold text-transparent bg-gradient-purple2 bg-clip-text w-full"
              >
                0 %
              </h2>
              <img
                src="https://sbm-final-project-fe.vercel.app/humid_icon.png"
                alt=""
                class="absolute top-0 right-0 h-full"
              />
            </div>
          </div>
          <div
            class="drop-shadow-1 bg-white px-4 py-3 relative overflow-hidden rounded-[20px] w-[550px] container h-min"
          >
            <div
              class="flex justify-between mb-3 w-full lg:w-1/2 flex-shrink-0"
            >
              <h1
                class="text-[20px] text-transparent bg-gradient-purple2 bg-clip-text font-semibold"
              >
                Status Chart
              </h1>
            </div>
            <div>
              <canvas id="DHTChart"></canvas>
            </div>
          </div>
          <div class="flex gap-5">
            <div
              class="drop-shadow-1 bg-white px-4 py-3 rounded-[20px] container w-fit"
            >
              <div class="flex justify-between items-end mb-3">
                <h1
                  class="text-[20px] text-transparent bg-gradient-purple2 bg-clip-text font-semibold"
                >
                  Car Status
                </h1>
                <div
                  class="flex items-center gap-3 bg-gradient-green1 text-transparent bg-clip-text font-bold"
                >
                  <span
                    class="block w-[10px] h-[10px] rounded-full bg-gradient-green1"
                  ></span>
                  Monitoring
                </div>
              </div>
              <div class="flex flex-col gap-10">
                <div class="w-full flex justify-center">
                  <div>
                    <h1
                      class="text-[#828282] text-center text-[14px] font-semibold"
                    >
                      Time (hh:mm:ss)
                    </h1>
                    <h2
                      id="timePassed"
                      class="text-[30px] font-bold text-transparent bg-gradient-purple2 bg-clip-text w-full text-center"
                    >
                      00:00:00
                    </h2>
                  </div>
                </div>
                <div class="flex gap-10 justify-center">
                  <div>
                    <h1
                      class="text-[#828282] text-center text-[14px] font-semibold"
                    >
                      Distance (cm)
                    </h1>
                    <h2
                      id="distance"
                      class="text-[30px] font-bold text-transparent bg-gradient-purple2 bg-clip-text w-full text-center"
                    >
                      0
                    </h2>
                  </div>
                  <div>
                    <h1
                      class="text-[#828282] text-center text-[14px] font-semibold"
                    >
                      Speed (cm/s)
                    </h1>
                    <h2
                      id="speed"
                      class="text-[30px] font-bold text-transparent bg-gradient-purple2 bg-clip-text w-full text-center"
                    >
                      0
                    </h2>
                  </div>
                </div>
                <div class="grid grid-cols-3 gap-5">
                  <div>
                    <h1
                      class="text-[#828282] text-center text-[14px] font-semibold"
                    >
                      Accel. X (m/s<sup>2</sup>)
                    </h1>
                    <h2
                      id="accelerationX"
                      class="text-[30px] font-bold text-transparent bg-gradient-purple2 bg-clip-text w-full text-center"
                    >
                      0
                    </h2>
                  </div>
                  <div>
                    <h1
                      class="text-[#828282] text-center text-[14px] font-semibold"
                    >
                      Accel. Y (m/s<sup>2</sup>)
                    </h1>
                    <h2
                      id="accelerationY"
                      class="text-[30px] font-bold text-transparent bg-gradient-purple2 bg-clip-text w-full text-center"
                    >
                      0
                    </h2>
                  </div>
                  <div>
                    <h1
                      class="text-[#828282] text-center text-[14px] font-semibold"
                    >
                      Accel. Z (m/s<sup>2</sup>)
                    </h1>
                    <h2
                      id="accelerationZ"
                      class="text-[30px] font-bold text-transparent bg-gradient-purple2 bg-clip-text w-full text-center"
                    >
                      0
                    </h2>
                  </div>
                  <div>
                    <h1
                      class="text-[#828282] text-center text-[14px] font-semibold"
                    >
                      Roll Drift (°)
                    </h1>
                    <h2
                      id="rollDrift"
                      class="text-[30px] font-bold text-transparent bg-gradient-purple2 bg-clip-text w-full text-center"
                    >
                      0
                    </h2>
                  </div>
                  <div>
                    <h1
                      class="text-[#828282] text-center text-[14px] font-semibold"
                    >
                      Pitch Drift (°)
                    </h1>
                    <h2
                      id="pitchDrift"
                      class="text-[30px] font-bold text-transparent bg-gradient-purple2 bg-clip-text w-full text-center"
                    >
                      0
                    </h2>
                  </div>
                  <div>
                    <h1
                      class="text-[#828282] text-center text-[14px] font-semibold"
                    >
                      Yaw Drift (°)
                    </h1>
                    <h2
                      id="yawDrift"
                      class="text-[30px] font-bold text-transparent bg-gradient-purple2 bg-clip-text w-full text-center"
                    >
                      0
                    </h2>
                  </div>
                  <div>
                    <h1
                      class="text-[#828282] text-center text-[14px] font-semibold"
                    >
                      Misalignment (°)
                    </h1>
                    <h2
                      id="misalignmentAngle"
                      class="text-[30px] font-bold text-transparent bg-gradient-purple2 bg-clip-text w-full text-center"
                    >
                      0
                    </h2>
                  </div>
                </div>
              </div>
            </div>
            <div
            class="drop-shadow-1 bg-white px-4 py-3 relative overflow-hidden rounded-[20px] w-[550px] container h-min"
          >
            <div
              class="flex justify-between mb-3 w-full lg:w-1/2 flex-shrink-0"
            >
              <h1
                class="text-[20px] text-transparent bg-gradient-purple2 bg-clip-text font-semibold"
              >
                Distance & Speed Chart
              </h1>
            </div>
            <div>
              <canvas id="distanceSpeedChart"></canvas>
            </div>
          </div>
          </div>
          <div
            class="drop-shadow-1 bg-white px-4 py-3 relative overflow-hidden rounded-[20px] w-[550px] container h-min"
          >
            <div
              class="flex justify-between mb-3 w-full lg:w-1/2 flex-shrink-0"
            >
              <h1
                class="text-[20px] text-transparent bg-gradient-purple2 bg-clip-text font-semibold"
              >
                Acceleration Chart
              </h1>
            </div>
            <div>
              <canvas id="AccelerationChart"></canvas>
            </div>
          </div>
          <div
            class="drop-shadow-1 bg-white px-4 py-3 relative overflow-hidden rounded-[20px] w-[550px] container h-min"
          >
            <div
              class="flex justify-between mb-3 w-full lg:w-1/2 flex-shrink-0"
            >
              <h1
                class="text-[20px] text-transparent bg-gradient-purple2 bg-clip-text font-semibold"
              >
                Gyro Chart
              </h1>
            </div>
            <div>
              <canvas id="GyroChart"></canvas>
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
    .indicator-dark {
      background-color: #16181b !important;
    }
  </style>
  <script defer>
    const body = document.querySelector("body");
    const espIP = window.location.host;
    const timeOpened = Date.now();
    const timePassed = document.querySelector("#timePassed");

    setInterval(() => {
      const timeNow = Date.now();
      const timeDiff = new Date(timeNow - timeOpened);
      const secondsPassed = Math.floor(timeDiff.getTime() / 1000) % 60;
      const hoursString = timeDiff.getUTCHours().toString().padStart(2, "0");
      const minutesString = timeDiff
        .getUTCMinutes()
        .toString()
        .padStart(2, "0");
      const secondsString = secondsPassed.toString().padStart(2, "0");
      timePassed.innerHTML = `${hoursString}:${minutesString}:${secondsString}`;
    }, 1000);

    if (localStorage.getItem("theme") === "dark") {
      body.classList.add("dark");
      document.querySelectorAll(".container").forEach((container) => {
        container.classList.add("container-dark");
      });
      document
        .querySelector("#active-indicator")
        .classList.add("indicator-dark");
    }

    const DHTChart = document.getElementById("DHTChart");
    const temperatures = [];
    const humidities = [];
    const labels = [];
    const chart1 = new Chart(DHTChart, {
      type: "line",
      data: {
        labels: labels,
        datasets: [
          {
            label: "Temperature (°C)",
            data: temperatures,
            borderWidth: 1,
            backgroundColor: "#5740B4",
            borderColor: "#5740B4",
          },
          {
            label: "Humidity (%)",
            data: humidities,
            borderWidth: 1,
            backgroundColor: "#2A58D0",
            borderColor: "#2A58D0",
          },
        ],
      },
      options: {
        borderWidth: 10,
        scales: {
          y: {
            beginAtZero: true,
            grid: {
              color:
                localStorage.getItem("theme") == "dark"
                  ? "#f5f5f522"
                  : "#16181B44",
            },
          },
          x: {
            grid: {
              color:
                localStorage.getItem("theme") == "dark"
                  ? "#f5f5f522"
                  : "#16181B44",
            },
          },
        },
      },
    });

    const MPUChart = document.getElementById("AccelerationChart");
    const accelXs = [];
    const accelYs = [];
    const accelZs = [];
    const chart2 = new Chart(MPUChart, {
      type: "line",
      data: {
        labels: labels,
        datasets: [
          {
            label: "Accel X (m/s²)",
            data: accelXs,
            borderWidth: 1,
            backgroundColor: "#5740B4",
            borderColor: "#5740B4",
          },
          {
            label: "Accel Y (m/s²)",
            data: accelYs,
            borderWidth: 1,
            backgroundColor: "#2A58D0",
            borderColor: "#2A58D0",
          },
          {
            label: "Accel Z (m/s²)",
            data: accelZs,
            borderWidth: 1,
            backgroundColor: "rgba(66, 145, 180)",
            borderColor: "rgba(66, 145, 180)",
          },
        ],
      },
      options: {
        borderWidth: 10,
        scales: {
          y: {
            beginAtZero: true,
            grid: {
              color:
                localStorage.getItem("theme") == "dark"
                  ? "#f5f5f522"
                  : "#16181B44",
            },
          },
          x: {
            grid: {
              color:
                localStorage.getItem("theme") == "dark"
                  ? "#f5f5f522"
                  : "#16181B44",
            },
          },
        },
      },
    });

    const GyroChart = document.getElementById("GyroChart");
    const gyroXs = [];
    const gyroYs = [];
    const gyroZs = [];
    const chart3 = new Chart(GyroChart, {
      type: "line",
      data: {
        labels: labels,
        datasets: [
          {
            label: "Gyro X (°/s)",
            data: gyroXs,
            borderWidth: 1,
            backgroundColor: "#5740B4",
            borderColor: "#5740B4",
          },
          {
            label: "Gyro Y (°/s)",
            data: gyroYs,
            borderWidth: 1,
            backgroundColor: "#2A58D0",
            borderColor: "#2A58D0",
          },
          {
            label: "Gyro Z (°/s)",
            data: gyroZs,
            borderWidth: 1,
            backgroundColor: "rgba(66, 145, 180)",
            borderColor: "rgba(66, 145, 180)",
          },
        ],
      },
      options: {
        borderWidth: 10,
        scales: {
          y: {
            beginAtZero: true,
            grid: {
              color:
                localStorage.getItem("theme") == "dark"
                  ? "#f5f5f522"
                  : "#16181B44",
            },
          },
          x: {
            grid: {
              color:
                localStorage.getItem("theme") == "dark"
                  ? "#f5f5f522"
                  : "#16181B44",
            },
          },
        },
      },
    });

    const speedDistanceChart = document.getElementById("SpeedDistanceChart");
    const speeds = [];
    const distances = [];
    const chart4 = new Chart(speedDistanceChart, {
      type: "line",
      data: {
        labels: labels,
        datasets: [
          {
            label: "Speed (m/s)",
            data: speeds,
            borderWidth: 1,
            backgroundColor: "#5740B4",
            borderColor: "#5740B4",
          },
          {
            label: "Distance (m)",
            data: distances,
            borderWidth: 1,
            backgroundColor: "#2A58D0",
            borderColor: "#2A58D0",
          },
        ],
      },
      options: {
        borderWidth: 10,
        scales: {
          y: {
            beginAtZero: true,
            grid: {
              color:
                localStorage.getItem("theme") == "dark"
                  ? "#f5f5f522"
                  : "#16181B44",
            },
          },
          x: {
            grid: {
              color:
                localStorage.getItem("theme") == "dark"
                  ? "#f5f5f522"
                  : "#16181B44",
            },
          },
        },
      },
    });

    const websocket = new WebSocket(`ws://${espIP}/ws`);
    websocket.addEventListener("open", (event) => {
      websocket.send("Hello Server!");
    });

    websocket.addEventListener("message", (event) => {
      const temperature = document.querySelector("#temperature");
      temperature.innerHTML = JSON.parse(event.data).temperature + " °C";
      if (temperatures.length > 10) {
        temperatures.shift();
        labels.shift();
      }
      temperatures.push(JSON.parse(event.data).temperature);
      const now = new Date();

      labels.push(
        `${now.getHours() < 10 ? "0" + now.getHours() : now.getHours()}:${
          now.getMinutes() < 10 ? "0" + now.getMinutes() : now.getMinutes()
        }:${now.getSeconds() < 10 ? "0" + now.getSeconds() : now.getSeconds()}`
      );

      const humidity = document.querySelector("#humidity");
      humidity.innerHTML = JSON.parse(event.data).humidity + " %";
      if (humidities.length > 10) {
        humidities.shift();
      }
      humidities.push(JSON.parse(event.data).humidity);

      const accelerationX = document.querySelector("#accelerationX");
      accelerationX.innerHTML = JSON.parse(event.data).accelerationX;
      if (accelXs.length > 10) {
        accelXs.shift();
      }
      accelXs.push(JSON.parse(event.data).accelerationX);

      const accelerationY = document.querySelector("#accelerationY");
      accelerationY.innerHTML = JSON.parse(event.data).accelerationY;
      if (accelYs.length > 10) {
        accelYs.shift();
      }
      accelYs.push(JSON.parse(event.data).accelerationY);

      const accelerationZ = document.querySelector("#accelerationZ");
      accelerationZ.innerHTML = JSON.parse(event.data).accelerationZ;
      if (accelZs.length > 10) {
        accelZs.shift();
      }
      accelZs.push(JSON.parse(event.data).accelerationZ);

      const pitch = document.querySelector("#pitchDrift");
      pitch.innerHTML = JSON.parse(event.data).rotationY;
      if (gyroYs.length > 10) {
        gyroYs.shift();
      }
      gyroYs.push(JSON.parse(event.data).rotationY);

      const roll = document.querySelector("#rollDrift");
      roll.innerHTML = JSON.parse(event.data).rotationX;
      if (gyroXs.length > 10) {
        gyroXs.shift();
      }
      gyroXs.push(JSON.parse(event.data).rotationX);

      const yaw = document.querySelector("#yawDrift");
      yaw.innerHTML = JSON.parse(event.data).rotationZ;
      if (gyroZs.length > 10) {
        gyroZs.shift();
      }
      gyroZs.push(JSON.parse(event.data).rotationZ);

      const speed = document.querySelector("#speed");
      speed.innerHTML = JSON.parse(event.data).speed;
      if(speeds.length > 10) {
        speeds.shift();
      }
      speeds.push(JSON.parse(event.data).speed);

      const distance = document.querySelector("#distance");
      distance.innerHTML = JSON.parse(event.data).distance;
      if(distances.length > 10) {
        distances.shift();
      }
      distances.push(JSON.parse(event.data).distance);

      const misalignmentAngle = document.querySelector("#misalignmentAngle");
      misalignmentAngle.innerHTML = JSON.parse(event.data).missAngle;

      chart1.data.datasets[0].data = temperatures;
      chart1.data.labels = labels;
      chart1.update();

      chart2.data.datasets[0].data = accelXs;
      chart2.data.datasets[1].data = accelYs;
      chart2.data.datasets[2].data = accelZs;
      chart2.data.labels = labels;
      chart2.update();

      chart3.data.datasets[0].data = gyroXs;
      chart3.data.datasets[1].data = gyroYs;
      chart3.data.datasets[2].data = gyroZs;
      chart3.data.labels = labels;
      chart3.update();

      chart4.data.datasets[0].data = speeds;
      chart4.data.datasets[1].data = distances;
      chart4.data.labels = labels;
      chart4.update();
    });
  </script>
</html>
)HTML";

#endif