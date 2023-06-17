#ifndef SETTINGS_PAGE_H_
#define SETTINGS_PAGE_H_

String settingsPage = R"HTML(
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
        class="fixed top-0 py-10 w-[277px] flex flex-col gap-10 h-screen text-white bg-gradient-purple1 flex flex-col justify-between items-center"
      >
        <img
          class="px-5"
          src="https://sbm-final-project-fe.vercel.app/Logo.png"
        />
        <ul class="text-[24px] w-full flex flex-col items-center relative">
          <div
            id="active-indicator"
            class="absolute right-0 top-0 bg-[#F5F5F5] w-[95%] h-[33%] rounded-l-full translate-y-[100%]"
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
            <a class="flex items-center gap-3 font-semibold !text-[#5740B4]" href="/settings">
              <img
                class="w-[30px]"
                src="https://sbm-final-project-fe.vercel.app/SettingsActive.png"
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
            Settings
          </h1>
          <div class="w-full bg-gradient-purple2 h-[4px] rounded-full"></div>
        </div>
        <main class="flex flex-col gap-5 py-5">
          <div class="flex items-center gap-3">
            <h1 class="text-inherit text-[20px]">Dark Mode</h1>
            <button id="toggle-theme" class="w-[60px]">
              <div
                class="w-full h-full p-1 bg-gradient-purple1 outline outline-white outline-1 rounded-full"
              >
                <div
                  id="theme-slider"
                  class="w-1/2 bg-white h-full aspect-square rounded-full transition duration-300"
                ></div>
              </div>
            </button>
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
      color: white;
    }
    .indicator-dark {
      background-color: #16181b !important;
    }
  </style>
  <script>
    const toggleTheme = document.getElementById("toggle-theme");
    const savedTheme = localStorage.getItem("theme");
    const themeSlider = document.getElementById("theme-slider");
    toggleTheme.addEventListener("click", () => {
      document.querySelector("body").classList.toggle("dark");
      themeSlider.classList.toggle("translate-x-[100%]");
      localStorage.setItem("theme", savedTheme == "light" ? "dark" : "light");
      document.querySelector("#active-indicator").classList.toggle("indicator-dark");
    });

    const storedTheme = localStorage.getItem("theme");
    if (storedTheme === "dark") {
      document.querySelector("body").classList.add("dark");
      themeSlider.classList.add("translate-x-[100%]");
      document.querySelector("#active-indicator").classList.add("indicator-dark");
    }
  </script>
</html>
)HTML";

#endif