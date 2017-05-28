using System;
using System.Xml;
using System.Xml.Serialization;
using System.Xml.Schema;

namespace client
{
	public abstract class CommandBase: IXmlSerializable
	{
		public CommandBase ()
		{
		}


		public XmlSchema GetSchema () {
			return null;
		}

		public void ReadXml (XmlReader reader){
			throw new NotImplementedException ();
		}

		public abstract void WriteXml (XmlWriter writer);

	}
}

