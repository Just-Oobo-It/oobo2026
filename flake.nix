{ pkgs }:
pkgs.mkShell {
	nativeBuildInputs = with pkgs; [
		pkg-config
		make
	];

	buildInputs = with pkgs; [
		SDL2
	];
}
