{
  description = "Nix development environment for NodeJS";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-24.05";
    # Use nixpkgs pinned to https://github.com/NixOS/nixpkgs/pull/343743 so that -O3 works as expected
    nixpkgs-unstable.url = "github:nixos/nixpkgs/pull/343743/head";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, nixpkgs-unstable, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };

        pkgs-unstable = import nixpkgs-unstable {
          inherit system;
        };
      in
      {
        devShells.default = pkgs.mkShell {
          packages = [
            pkgs.nodejs_20
            pkgs.jq
            pkgs.nodePackages.typescript
            pkgs.python312
            pkgs.binaryen
            pkgs-unstable.emscripten
          ];

          shellHook = ''
            node --version

            # This is not ideal, but the emscripten package applies certain patches to
            # ensure clang finds the libraries and required files.
            cp -f ${pkgs-unstable.emscripten}/share/emscripten/emcc.py ./

            export EM_CONFIG=${pkgs-unstable.emscripten}/share/emscripten/.emscripten
          '';
        };
      }
    );
}
