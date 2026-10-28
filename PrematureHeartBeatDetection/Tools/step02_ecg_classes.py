"""Map PhysioNet BIDMC ``.ecg`` symbols to source classes.

The letters are the PhysioNet beat-annotation alphabet. This map is beat
type only. It does not describe where the electrodes were placed.
``R`` (bundle-branch) stays with normal. ``r`` is R-on-T PVC.
``map_symbol`` returns None for markers that are not beats. Step 04 drops
the ``unclassified`` class.
"""

from __future__ import annotations

# Studio class names (no spaces). ECG5000 IDs 1–5.
CLASS_NAMES = [
    "normal",
    "r_on_t_pvc",
    "pvc",
    "supraventricular",
    "unclassified",
]

CLASS_LABELS = {
    "normal": "Normal (N)",
    "r_on_t_pvc": "R-on-T PVC",
    "pvc": "Premature ventricular contraction",
    "supraventricular": "Supraventricular premature / ectopic",
    "unclassified": "Unclassified beat",
}

# PhysioNet beat-annotation alphabet:
#   https://archive.physionet.org/physiobank/annotations.shtml
# F is ventricular fusion in that alphabet. ECG5000 treats it as R-on-T,
# and this map follows that 5-class convention.
_SYMBOL_TO_CLASS: dict[str, str] = {
    "N": "normal",
    "L": "normal",
    "R": "normal",  # annotation alphabet: bundle-branch beat, not R-on-T
    "B": "normal",
    "e": "normal",
    "j": "normal",
    "n": "normal",
    "V": "pvc",
    "E": "pvc",
    "r": "r_on_t_pvc",
    "F": "r_on_t_pvc",
    "A": "supraventricular",
    "a": "supraventricular",
    "J": "supraventricular",
    "S": "supraventricular",
    "Q": "unclassified",
    "/": "unclassified",
    "f": "unclassified",
    "P": "unclassified",
    "p": "unclassified",
    "U": "unclassified",
    "?": "unclassified",
    "x": "unclassified",
    "|": "unclassified",
}


def map_symbol(symbol: str) -> str | None:
    """Return a Studio class name, or None to drop non-beat markers."""
    if not symbol:
        return None
    return _SYMBOL_TO_CLASS.get(symbol)
