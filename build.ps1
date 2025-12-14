$env:Path += ";C:\msys64\mingw64\bin"
g++ sdl2.cpp -o game.exe -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib -lmingw32 -lSDL2main -lSDL2
if ($LASTEXITCODE -eq 0) {
    Write-Host "Build successful! Running game..."
    ./game.exe
} else {
    Write-Host "Build failed."
}
