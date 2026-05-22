async function update() {
  try {
    const res = await fetch("telemetry/system_state.json");
    const data = await res.json();

    const c = data.coherence ?? 0;

    // PIU DIAL
    document.getElementById("piuValue").innerText =
      Math.round(c * 100) + "%";

    // GAUGES
    setBar("cohBar", c);
    setBar("sigBar", c * 0.8);
    setBar("loadBar", 1 - c);
    setBar("greenBar", c * 0.6);

    // DISPLAY
    document.getElementById("line1").innerText = "> SYSTEM ACTIVE";
    document.getElementById("line2").innerText = "> COHERENCE: " + c.toFixed(3);
    document.getElementById("line3").innerText = "> MODE: " + (data.mode || "live");

  } catch (e) {
    document.getElementById("line1").innerText =
      "> WAITING FOR ENGINE...";
  }
}

function setBar(id, value) {
  const el = document.getElementById(id);
  if (el) el.style.width = (value * 100) + "%";
}

setInterval(update, 1000);
update();
