using System;

namespace Client
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			if (args.Length > 0) {
				var addresParts = args [0].Split (new[] { ':' }, 2);
				int port = 0;
				if (addresParts.Length == 2
				    && int.TryParse (addresParts [1], out port)
				    && port > 0) {
					Console.Write (string.Format("Łączenie z {0}:{1} ...", addresParts[0], port));
					var client = new Client (addresParts [0], port);
					Console.WriteLine (" połączono");
					while (true) {
						var command = Console.ReadLine ().ToLower ().Split(new []{' '}, 2);
						var parameters = command.Length == 1 ? new string[0] : command[1].Split(new []{' '});
						switch (command[0].Trim()) {
						case "list":
						case "l":
							Console.WriteLine (client.ListInterfaces ());
							break;
						case "details":
						case "d":
							Console.WriteLine (client.Details (parameters));
							break;
					
						case "quit":
						case "q":
							return;
						default:
							Console.WriteLine ("Dostępne komendy:");
							Console.WriteLine (" l(ist) - zwraca listę interfejsów na wskazanej maszynie");

							Console.WriteLine (" q(uit) - kończy sesję");
							break;
						}
					}
				}				
			}
			Console.WriteLine ("Użycie: client <adres:port>");
		}
	}

}
