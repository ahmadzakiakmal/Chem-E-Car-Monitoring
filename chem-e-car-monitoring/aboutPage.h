#ifndef ABOUT_PAGE_H_
#define ABOUT_PAGE_H_

String aboutPage = R"HTML(
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
        class="fixed top-0 py-10 w-[277px] flex flex-col gap-10 h-screen text-white bg-gradient-purple1 flex flex-col justify-between items-center"
      >
        <img
          class="px-5"
          src="https://sbm-final-project-fe.vercel.app/Logo.png"
        />
        <ul class="text-[24px] w-full flex flex-col items-center relative">
          <div
            id="active-indicator"
            class="absolute right-0 top-0 bg-[#F5F5F5] w-[95%] h-[33%] rounded-l-full translate-y-[200%]"
          ></div>
          <li class="py-3 z-[2]">
            <a href="/" class="flex items-center gap-3">
              <img
                class="h-[28px] mt-[-3px]"
                src="https://sbm-final-project-fe.vercel.app/Home.png"
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
          <li class="py-3 z-[2] text-[#5740B4] font-semibold">
            <a class="flex items-center gap-3" href="/about.html">
              <img
                class="w-[30px]"
                src="https://sbm-final-project-fe.vercel.app/AboutActive.png"
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
            class="text-[24px] font-semibold bg-gradient-purple2 text-transparent bg-clip-text about-ul"
          >
            About
          </h1>
          <div class="w-full bg-gradient-purple2 h-[4px] rounded-full" ></div>
        </div>
        <main class="py-5" id="about">
          <div
            class="drop-shadow-1 relative bg-white px-4 py-3 overflow-hidden rounded-[20px] container"
          >
            <h1
              class="text-transparent bg-gradient-purple2 bg-clip-text text-[22px] font-bold underline underline-[#5740B4] about-ul"
            >
              Our Team:
            </h1>
            <ul class="about-ul text-transparent bg-clip-text bg-gradient-purple2 w-fit">
              <li class="w-fit">
                <a
                  class="w-fit block hover:text-[#5740B4]"
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
                  class="w-fit block font-semibold hover:text-[#5740B4]"
                  href="https://github.com/ahmadzaki2975"
                >
                  <h1>Ahmad Zaki Akmal</h1>
                </a>
                <h2>21/480179/TK/52981</h2>
              </li>
              <li class="w-fit">
                <a
                  class="w-fit block hover:text-[#5740B4] font-semibold"
                  href="https://github.com/aufarhmn"
                >
                  <h1>Aufa Nasywa Rahman</h1>
                </a>
                <h2>21/475255/TK/52454</h2>
              </li>
              <li class="w-fit">
                <a
                  class="w-fit block hover:text-[#5740B4] font-semibold"
                  href="https://github.com/DiftaFitrahul"
                >
                  <h1>Difta Fitrahul Qihaj</h1>
                </a>
                <h2>21/480096/TK/52975</h2>
              </li>
              <li class="w-fit">
                <a
                  class="w-fit block hover:text-[#5740B4] font-semibold"
                  href="https://github.com/gigahidjrikaaa"
                >
                  <h1>Giga Hidjrika Aura Adkhy</h1>
                </a>
                <h2>21/479228/TK/52833</h2>
              </li>
            </ul>
          </div>
          <div
            class="drop-shadow-1 relative bg-white px-4 py-3 overflow-hidden rounded-[20px] mt-5 container"
          >
            <h1
              class="text-transparent bg-clip-text bg-gradient-purple2 text-[22px] font-bold underline underline-[#5740B4] about-ul"
            >
              Quick Links:
            </h1>
            <a
              class="text-transparent bg-clip-text bg-gradient-purple2 hover:text-[#5740B4] font-semibold about-ul"
              href="https://github.com/ahmadzaki2975/Chem-E-Car-Monitoring"
            >
              Main Repository
            </a>
            <p class="text-transparent bg-clip-text bg-gradient-purple2">
              The repository containing the code for the ESP32
            </p>
            <a
              class="text-transparent bg-clip-text bg-gradient-purple2 hover:text-[#5740B4] font-semibold about-ul"
              href="https://github.com/ahmadzaki2975/SBM-Final-Project-HTML"
            >
              HTML Dev Repository
            </a>
            <p class="text-transparent bg-clip-text bg-gradient-purple2">
              The repository containing the code for the HTML during development
              phase.
            </p>
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
      color: inherit;
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
      color: white !important;
    }
    .container-dark {
      background-color: #0f0f0f;
      color: #b77bef !important;
      filter: drop-shadow(0px 0px 5px rgba(42, 88, 208));
    }
    .indicator-dark {
      background: #16181b !important;
    }
  </style>
  <script defer>
    const storedTheme = localStorage.getItem("theme");
    if (storedTheme === "dark") {
      document.querySelector("body").classList.add("dark");
      document.querySelectorAll(".container").forEach((container) => {
        container.classList.add("container-dark");
      });
      document.querySelector("#active-indicator").classList.add("indicator-dark");
    }
  </script>
</html>
)HTML";

#endif