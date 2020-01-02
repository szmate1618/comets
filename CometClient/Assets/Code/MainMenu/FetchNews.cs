using System;
using System.IO;
using System.Net;
using System.Net.Security;
using System.Security.Cryptography.X509Certificates;
using UnityEngine;
using UnityEngine.UI;


public class FetchNews : MonoBehaviour
{

	//This is from https://stackoverflow.com/questions/4926676/mono-https-webrequest-fails-with-the-authentication-or-decryption-has-failed.
	public bool MyRemoteCertificateValidationCallback(
		System.Object sender,
		X509Certificate certificate,
		X509Chain chain,
		SslPolicyErrors sslPolicyErrors)
	{
		return true;
	}

	private string ParseNews(string rawText)
	{
		return "asdsadas";
	}

	public void Start ()
	{
		ServicePointManager.ServerCertificateValidationCallback = MyRemoteCertificateValidationCallback;

		string html;
		string newsUrl = @"https://szmate1618.github.io/comets-website/news/recent.html";

		HttpWebRequest request = (HttpWebRequest)WebRequest.Create(newsUrl);
		//request.AutomaticDecompression = DecompressionMethods.GZip;

		using (HttpWebResponse response = (HttpWebResponse)request.GetResponse())
		using (Stream stream = response.GetResponseStream())
		using (StreamReader reader = new StreamReader(stream))
		{
			html = reader.ReadToEnd();
		}

		GetComponent<Text>().text = ParseNews(html);
	}
}
