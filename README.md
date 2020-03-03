## sample-project

Παράδειγμα δομής ενός C project. Επιδεικνύει τη χρήση modules, Makefiles και tests.

### Παράδειγμα χρήσης

```bash
cd programs/minmax

make minmax
./minmax 3 -1 12 412

make clean
```

### Χρήση από το VS Code

- `Ctrl-Shift-B` : compile & execute
- `F5` : debug
- Ρυθμίσεις στο `.vscode/settings.json`

### Project structure

- `include`

  Κοινόχρηστα include files (μπορούν να χρησιμοποιηθούν από οποιοδήποτε πρόγραμμα ή module).

- `lib`

  Κοινόχρηστες βιβλιοθήκες. Εκτελώντας `make` σε αυτό το directory παράγεται η βιβλιοθήκη
  `k08.a` η οποία περιέχει υλοποιήσεις από όλα τα ADTs.

- `programs`

  Εκτελέσιμα προγράμματα.

- `modules`

  Υλοποιήσεις των κοινόχρηστων modules.

- `tests`

  Tests για κοινόχρηστα modules.