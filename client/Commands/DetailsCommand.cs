using System;
using System.Xml.Serialization;

namespace Client.Commands
{
	[XmlRoot("Details")]
	public class DetailsCommand: ICommand
	{
		private readonly string[] _interfaces;

		public DetailsCommand () 
		{
			throw new ApplicationException ("Default constructor left only to allow serialization");
		}

		public DetailsCommand (string[] interfaces)
		{
			_interfaces = interfaces;
		}

		[XmlElement("Interface")]
		public string[] Interfaces { get { return _interfaces; } set { } }

	}
}

