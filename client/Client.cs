using System;
using System.Net.Sockets;
using System.Text;

namespace Client
{
	public class Client
	{
		private readonly TcpClient _client;
		private readonly NetworkStream _clientStream;
		private readonly byte[] _readBuffer = new byte[0x400];

		private const string NoResponseReceived = "Nie otrzymano odpowiedzi z serwera w oczekiwanym czasie";
		private const string ServerDisconnected = "Serwer zdalny niespodziewanie zakończył połączenie";

		public Client (string address, int port)
		{
			_client = new TcpClient (address, port);
			_clientStream = _client.GetStream ();
			_clientStream.ReadTimeout = 2000;
		}

		public string ListInterfaces(){
			return Query (Commands.ListCommand.Instance);
		}

		public string Details(string[] interfaces)
		{
			return Query (new Commands.DetailsCommand (interfaces));
		}


		private string Query(Commands.ICommand command)
		{
			string query = Helpers.SerializationHelper.Serialize (command);
			byte[] buffer = Encoding.ASCII.GetBytes (query);
			try
			{
				_clientStream.Write (buffer, 0, buffer.Length);
				int nRead = _clientStream.Read (_readBuffer, 0, _readBuffer.Length);
				if (nRead > 0)
					return Encoding.ASCII.GetString (_readBuffer, 0, nRead);
				return NoResponseReceived;
			}
			catch (System.IO.IOException) {
				return ServerDisconnected;
			}
		}

	}
}

