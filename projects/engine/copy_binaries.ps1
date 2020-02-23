$script_path = split-path -parent $MyInvocation.MyCommand.Definition
$libs_path = "$script_path\..\..\libraries\"
$file_pattern = "*.dll"

foreach ($build_type in ("Debug", "Release")) {
    $destination = "$script_path\..\vs_output\engine\$build_type"
    if (Test-Path $destination) {
        Write-Output "Copying 3rd party dlls into: $destination"
        Get-ChildItem -Path "$libs_path" -Include "$file_pattern" -Recurse | Copy-Item -Destination "$destination" -Verbose
    }
}
