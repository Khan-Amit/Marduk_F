async function updateUI() {
    try {
        const res = await fetch("telemetry/system_state.json");
        const data = await res.json();

        document.getElementById("coherence").innerText =
            "Coherence: " + (data.coherence ?? 0).toFixed(4);

        document.getElementById("status").innerText =
            "Status: " + (data.status ?? "waiting");

        document.getElementById("mode").innerText =
            "Mode: " + (data.mode ?? "offline");

    } catch (e) {
        document.getElementById("status").innerText =
            "Status: waiting for pipeline...";
    }
}

setInterval(updateUI, 1000);
updateUI();
