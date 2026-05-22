async function updateSystem() {
    try {
        const res = await fetch("telemetry/system_state.json");
        const data = await res.json();

        document.getElementById("coherence").innerText =
            "Coherence: " + data.coherence.toFixed(4);

        document.getElementById("status").innerText =
            "Status: " + data.status;

        document.getElementById("mode").innerText =
            "Mode: " + data.mode;

    } catch (e) {
        document.getElementById("status").innerText =
            "Status: waiting for engine...";
    }
}

setInterval(updateSystem, 1000);
updateSystem();
