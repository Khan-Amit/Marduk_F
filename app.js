const terminal = document.getElementById("terminalOutput");
const piuValue = document.getElementById("piuValue");

/* TELEMETRY LOGS */

const telemetryLogs = [

  "> WEATHER STREAM ACTIVE",
  "> WIND TELEMETRY SYNCHRONIZED",
  "> SOLAR FLUX STABLE",
  "> SWB-SA STORAGE NOMINAL",
  "> PIU LOAD BALANCED",
  "> THERMAL ENVELOPE STABLE",
  "> GRID OFFSET CALCULATED",
  "> RENEWABLE MODE ACTIVE"

];

/* RANDOM TELEMETRY */

function addTelemetryLog() {

  const log = document.createElement("p");

  const randomLog =
    telemetryLogs[
      Math.floor(Math.random() * telemetryLogs.length)
    ];

  log.textContent = randomLog;

  terminal.appendChild(log);

  terminal.scrollTop = terminal.scrollHeight;

  /* LIMIT TERMINAL LINES */

  if (terminal.children.length > 18) {
    terminal.removeChild(terminal.children[0]);
  }
}

/* PIU ANIMATION */

function updatePIU() {

  const value = Math.floor(
    Math.random() * (95 - 70) + 70
  );

  piuValue.textContent = value + "%";

  /* COLOR STATES */

  if (value < 78) {

    piuValue.style.color = "#ff4d4d";

  } else if (value < 88) {

    piuValue.style.color = "#ffd24d";

  } else {

    piuValue.style.color = "#4da6ff";
  }
}

/* START BUTTON */

const startBtn =
  document.querySelectorAll(".normal")[0];

startBtn.addEventListener("click", () => {

  addTelemetryLog();

  telemetryInterval =
    setInterval(addTelemetryLog, 2000);

  piuInterval =
    setInterval(updatePIU, 2500);

});

/* PAUSE BUTTON */

const pauseBtn =
  document.querySelectorAll(".normal")[1];

pauseBtn.addEventListener("click", () => {

  clearInterval(telemetryInterval);
  clearInterval(piuInterval);

  const pauseLog =
    document.createElement("p");

  pauseLog.textContent =
    "> TELEMETRY STREAM PAUSED";

  terminal.appendChild(pauseLog);

});

/* STOP BUTTON */

const stopBtn =
  document.querySelector(".critical");

stopBtn.addEventListener("click", () => {

  clearInterval(telemetryInterval);
  clearInterval(piuInterval);

  const stopLog =
    document.createElement("p");

  stopLog.classList.add("alert");

  stopLog.textContent =
    "> SYSTEM TELEMETRY STOPPED";

  terminal.appendChild(stopLog);

  piuValue.textContent = "0%";
  piuValue.style.color = "#ff4d4d";

});

/* INITIALIZE */

updatePIU();
