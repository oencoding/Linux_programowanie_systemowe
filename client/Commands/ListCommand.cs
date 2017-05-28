using System;
using System.Xml.Serialization;

namespace Client.Commands
{
	[XmlRoot("List")]
	public class ListCommand: ICommand
	{
		public static ListCommand Instance { get; } = new ListCommand();
	}
}

