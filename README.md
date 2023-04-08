# ascii-grid

Transform any image into ascii charachters

█████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓█████████████████████▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓░░░░▒▒▒▒
███████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓███████████████████▓▓▓▒▒▒▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒
███████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓█████████████████▓▓▓▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒░░▒
█████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓████████████▓▓▓▓▓▓▓▓▒▒▒▒▒▒▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░
██████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░
█████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░
████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░
█████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░
▓█████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓█▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
▓▓████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▓▒▓███████████▓▓▒▒▒▒▒▒▒▒▒▒▒▒
▓▓▓▓███████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▓▓████████████▓▒▒▒▒▒▒▒▒▒▒
▓▓▓▓▓▓█████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▓███████████▓▒▒▒▒▒▒▒▒
▓▓▓▓▓▓▓▓███▓▓▓▓▓▓▓▓▓▓▓▓███▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▓██████▓▓▓▓█▒▒▒▒▒▒▒
▓▓▓▓▓▓▓▓▓███▓▓▓▓██████████▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒████▓▓▓▓▒▓█▒▒▒▒▒▒
▓▓▓▓▓▓▓▓▓▓▓██▓▒█████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒███▓▓▓▓▒▒▒▓░▒▒▒▒
▓▓▓▓▓▓▒▓▓▓▓▓█▒█████████▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒███▓▓▓▒▒▒▒█░▒▒▒▒
▓▓▓▓▓▓▓▒▒▓▓▓▓▓█████████▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓████▓▓▓▓▓▓▓▓▓▓▓▓▒▓███▓▓▒▒▒▒▒▓░▒▒▒▒
▓▓▓▓▓▓▓▓▓▒▒▓▒██████████▒▓▓▓▓▓▓▓▓███████████████████████▓▓▓▒▒▓███▓▓▓▒▒▒▒▒▒░▒▒▒▒
▓▓▓▓▓▓▓▓▓▓▒▒▒▓██████████▓▓▓▓███████████████▓▓▒▒▒▓▓█████████████▓▓▓▒▒▒▒▒▒░▒▒▒▒▒
▓▓▓▓▓▓▓▓▓▓▓▒▒▒█████████▓█████████████████▓▒▒▒▒▒▒▒▒▒▒▓████████▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒
▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒██████▓██████████████████▒▒░░░░░░░░░░░▒███████▓▓▒▒▒▒▒▒▒▒▒▒▒▒▓▒▒
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▓██▓▓██▓▓▓▓████████████▓▒░░░░░░░░░░░░░▓█████▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▓██▒▒▒▒▒▒▒██████████▒░░░░░░░░░░░░░░░████▓▓▓▓▓▒▒▓▒▒▒▒▒▒▒▒▒▒▒
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒██▒▒░▒░░░░▓█████████▒░░░░░░░░░░░░░░░████▓▓▓▒▒▒▒▒▓▒▒▒▒▒▒▒▒▒▒
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▓█░░░░░░░░░▒██████████░░░░░░░░░░░░░░░████▓▓▓▒▒▒▒▒▓▒▒▒▒▒▒▒▒▒▒
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░██░░░░░░░░░▓██████████▓░░░░░░░░░░░░░▓███▓▓▓▓▒▒▒▒▒▒▓░▒▒▒▒▒▒▒▒
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░█▓░░░░░░░░░█████████████▒░░░░░░░░▒▓████▓▓▓▓▒▒▒▒▒▒▒▓░▓▒▒▒▒▒▒▒
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░██░░░░░░░░▓████████████████▓▓▓▓███████▓▓▓▓▒▒▒▒▒▒▒▒▓░▓▓▒▒▒▒▒▒
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒█▒░░░░░░▓█████████████████████████▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒░▓▓▓▒▒▒▒▒
▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░██▓▒▒▒▒█████████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▒▒▒▒
▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▓████████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▓▓▓▓▓▓▒▒▒
▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░▓███████▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▒▓▓▓▓▓▓▓▒▒
▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▓▒▒██▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░▒▒▓▓▓▓▓▓▓▓▓▓▒
▒▒▓▓██▓███▓▓▓▓▓▓▒▒▒▒▓▒▒▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▓▓▓▓▓▓▓
░▒▒▓███████▓▓▓▓▓▓▒▒▒▒▓▓▓▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒░░
░░▒▒███████▓▓▓▓▓▓▓▒▒▒▒▒▒▓▓▓▒▒▒▒░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒
░░░░▒▒▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒░░
░░░░░░░░▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒
░░░░░░░░░░░░░▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒
░░░░░░░░░░░░░░░▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
▒▒░░░░░░░░░░░░░░░▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░
▒▒░░▒▒▒░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▒▒░░░░░░░░░░░░░░░▒░░░░░░░░░░░░░░░░░░░░░░░
░░░░░▒▒░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▓▓▓█░░░░░░░░░░░░░░░░░░░▒░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▓░░░░░░░░░░░░░░░░░░░▒░░░░░░░░░░░░░░░▒░▒░░░░
░░░░░░░░░▒▒░░░░▒░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▓░░░░░░░░░░░░░░░░░░▒░░░░░░░░░░░░░░░░▒░░░░░
░░░░░░░░░░░░░░▒▒▒▒▒▒▒░░░░░░▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░▓▒▒░░░░░▒▒░░░░░░░░░░░░░░░░░▒░░░░
░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░▒▒▒▒▒▒▒▒░░░░░░░░▒▒░░░░▒░░░░░▒░░░
░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒░░░░▒░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░▒░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▓█▓▒▓▓▒▓▓▒▒▒░▒▒▒▒▒▒▒▒▒▒░░▒▒░░▒▒░░▒░░░░▒░▒░░▒░
░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒░▒▒▒▓▓▓▓██▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▓▒▒▒▒▒▒░░░▒░░▓▓▓▒▒▒▓▓▓
░░░░░░░░░░░░░░░░░░░░░░░░▒░▒▓▓▒▒▒▒▒▒▒▒░░░░░░░░░░░▒▓▓▓░▒▒░░▒▒▒▒▒▒░░░▒░░░▒▒▓▓▓▓▓▓
░░░░░░░░░░░░░░░░░░░░░░░▒░▒▒░░░░░░░░░░░░░▒░░░░░░░░░▒░▒░▒░░░░░░░░░░▒░░░░░░░░▒▒▒▒
░░░░░░░░░░░░░░░▒▒▒▒░░░░░▒░░░▒▓▒▒▒░░░░▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒░░░▒█▒░░░▒▒▒▒▓▓▓▓▓▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒░▒▒▒░░░░░░░░░░▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
