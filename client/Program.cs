using System;

namespace Client
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			if (args.Length > 0) {
				var addresParts = args [0].Split (new[] { ':' }, 2);
				string host = "localhost";
				int port = 1060;
				if (addresParts.Length > 0)
				{
					host = addresParts[0];
					if (addresParts.Length > 1)
						int.TryParse(addresParts[1], out port);
				}
					Console.Write (string.Format("Łączenie z {0}:{1} ...", host, port));
					var client = new Client(host, port);
					Console.WriteLine (" połączono");
				while (true) {
					var command = Console.ReadLine ().ToLower ().Split (new []{ ' ' }, 2);
					var parameters = command.Length == 1 ? new string[0] : command [1].Split (new []{ ' ' });
					switch (command [0].Trim ()) {
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
			Console.WriteLine ("Użycie: client <adres:port>");
		}
	}

}
