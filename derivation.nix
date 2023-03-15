{ stdenv }:
stdenv.mkDerivation rec {
  name = "add-package-to-config-${version}";
  version = "1.0";

  src = ./.;

  nativeBuildInputs = [ ];
  buildInputs = [ ];

  buildPhase = ''
    gcc main.c -o add-package-to-config
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp add-package-to-config $out/bin
  '';
}
