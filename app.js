async function fetchState() {
    try {
        const res = await fetch("telemetry/system_state.json");
        const data = await res.json();

        document.getElementById("coherence").innerText =
            "Coherence: " + (data.coherence ?? 0).toFixed(4);

        document.getElementById("status").innerText =
            "Status: " + (data.status ?? "waiting");

        document.getElementById("mode").innerText =
            "Mode: " + (data.mode ?? "offline");

    } catch (err) {
        document.getElementById("status").innerText =
            "Status: waiting for C engine...";
    }
}

/* LIVE LOOP */
setInterval(fetchState, 1000);
fetchState();
