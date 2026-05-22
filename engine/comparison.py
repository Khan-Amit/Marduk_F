import json
import math

"""
Marduk_F™
Comparison & Field Validation Layer

Purpose:
- Load telemetry data from C engine output
- Compare node states
- Compute coherence deviation
- Detect anomalies in field behavior
"""

TELEMETRY_FILE = "../telemetry/telemetry.json"


def load_telemetry():
    with open(TELEMETRY_FILE, "r") as f:
        return json.load(f)


def compute_expected_coherence(nodes):
    """
    Expected model:
    coherence = average(field_strength - entropy)
    """
    if not nodes:
        return 0.0

    total = 0.0
    active = 0

    for n in nodes:
        if n.get("status") == "active":
            total += n["field_strength"] - n["entropy_level"]
            active += 1

    return total / 10.0  # normalized to system size (10 nodes)


def compute_actual_coherence(nodes):
    """
    Alternative real-world measured coherence
    (same formula for now, but separated for future divergence)
    """
    return compute_expected_coherence(nodes)


def detect_anomalies(nodes):
    anomalies = []

    for n in nodes:
        if n["entropy_level"] > n["field_strength"] * 2:
            anomalies.append({
                "node": n["node_id"],
                "type": "entropy_spike"
            })

        if n["field_strength"] < 0:
            anomalies.append({
                "node": n["node_id"],
                "type": "negative_field"
            })

    return anomalies


def compare_system():
    data = load_telemetry()
    nodes = data["nodes"]

    expected = compute_expected_coherence(nodes)
    actual = compute_actual_coherence(nodes)
    anomalies = detect_anomalies(nodes)

    deviation = abs(expected - actual)

    result = {
        "expected_coherence": expected,
        "actual_coherence": actual,
        "deviation": deviation,
        "anomaly_count": len(anomalies),
        "anomalies": anomalies
    }

    return result


if __name__ == "__main__":
    report = compare_system()

    print("\n=== MARDUK_F COMPARISON REPORT ===")
    print(f"Expected Coherence : {report['expected_coherence']:.4f}")
    print(f"Actual Coherence   : {report['actual_coherence']:.4f}")
    print(f"Deviation          : {report['deviation']:.4f}")
    print(f"Anomalies Found    : {report['anomaly_count']}")

    if report["anomalies"]:
        print("\n-- Anomalies --")
        for a in report["anomalies"]:
            print(a)
