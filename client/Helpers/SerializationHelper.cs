using System;
using System.IO;
using System.Xml;
using System.Xml.Serialization;

namespace Client.Helpers
{
	public static class SerializationHelper
	{
		public static string Serialize(object obj)
		{
			using (var outStream = new MemoryStream())
			{
				XmlWriterSettings xws = new XmlWriterSettings();
				xws.Encoding = System.Text.Encoding.UTF8;
				xws.Indent = true;
				using (var xtw = XmlTextWriter.Create (outStream, xws)) {
					var ser = new XmlSerializer (obj.GetType());
					XmlSerializerNamespaces ns = new XmlSerializerNamespaces ();
					ns.Add ("", "");
					ser.Serialize (xtw, obj, ns);
				}
				outStream.Position = 0;
				using (var sr = new StreamReader (outStream)) {
					return sr.ReadToEnd ();
				}
			}
		}

		public static T Deserialize<T>(string serialized, string xmlAttributeOverrides = null)
		{
			using (var inStream = new StringReader(serialized))
			{
				XmlSerializer ser;
				if (string.IsNullOrEmpty(xmlAttributeOverrides))
					ser = new XmlSerializer(typeof(T));
				else
					ser = new XmlSerializer(typeof(T), new XmlRootAttribute(xmlAttributeOverrides));
				return (T)ser.Deserialize(inStream);
			}
		}
	}
}

