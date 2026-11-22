{
  description = "Dev environment";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-26.05";
  };

  outputs = { self , nixpkgs ,... }: let
    system = "x86_64-linux";
  in {
    devShells."${system}".default = let
      pkgs = import nixpkgs { inherit system; };
    in pkgs.mkShell {
      nativeBuildInputs = with pkgs; [
        pkg-config
      ];

      packages = with pkgs; [
        zsh
        cmake
        gcc
        SDL2
        python3
        (pkgs.python3.withPackages (ps: [
            ps.pillow
        ]))
      ];

      shellHook = ''
        exec zsh
      '';
    };
  };
}
