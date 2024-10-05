set of int: Packages = 1..4; % 1: root, 2: menu, 3: dropdown, 4: icons
array[Packages] of string: PackageNames = ["root", "menu", "dropdown", "icons"];

array[1..6] of float: menu_versions = [1.0, 1.1, 1.2, 1.3, 1.4, 1.5];
array[1..5] of float: dropdown_versions = [1.8, 2.0, 2.1, 2.2, 2.3];
array[1..2] of float: icons_versions = [1.0, 2.0];

var 1..6: menu_selected_version;
var 1..5: dropdown_selected_version;
var 1..2: icons_selected_version;

constraint menu_selected_version >= 1 /\ menu_selected_version <= 6;
constraint dropdown_selected_version >= 1 /\ dropdown_selected_version <= 5;
constraint icons_selected_version >= 1 /\ icons_selected_version <= 2;

solve satisfy;

output [
    "root depends on: " ++
    "menu version " ++ show(menu_versions[menu_selected_version]) ++ ", " ++
    "dropdown version " ++ show(dropdown_versions[dropdown_selected_version]) ++ ", " ++
    "icons version " ++ show(icons_versions[icons_selected_version]) ++ "\n"
];
