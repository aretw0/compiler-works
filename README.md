Respositório para trabalhos da disciplina de compiladores.

Se usar o sublime eis os build system's que estou utilizando

"build_systems":
    [
        {
            "name": "cpp compiler all",
            // adicionar mais .cpp aqui para futuros builds
            "cmd": ["g++","-std=c++17", "-g", "main.cpp", "tradutor.cpp", "-o", "../bin/tradutor.out"],
            "working_dir" : "$file_path",
            "selector": "source.cpp"
        },
        {
            "name": "cpp compiler single",
            "cmd": ["g++", "-std=c++17", "-g","$file_name", "-o", "../bin/$file_base_name.out"],
            "working_dir" : "$file_path",
            "selector": "source.cpp"
        }
    ]
