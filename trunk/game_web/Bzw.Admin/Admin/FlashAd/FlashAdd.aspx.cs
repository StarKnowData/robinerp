using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using System.IO;
using Bzw.Data;
using BCST.Common;
using System.Xml;

public partial class Admin_FlashAd_FlashAdd : AdminBasePage
{

	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "01" );

	}
	protected void FlashAdds( object sender, EventArgs e )
	{
		string flashImg = "";
		string title, url;
        int id = 0;
		title = CommonManager.Web.RequestForm("title",""); 
        //if( title.ToString() == "" )
        //{
        //    CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\n标题不能为空！');", false);
        //    return;
        //}
		
		url = CommonManager.Web.RequestForm( "url", "" ); 
		if( url.ToString() == "" )
		{
			CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\nUrl连接地址不能为空！');", false);
			return;
		}

		

		#region 上传图片
		if( FileUpload1.HasFile )
		{
			string fileContentType = FileUpload1.PostedFile.ContentType;
			if(  fileContentType == "image/pjpeg" || fileContentType == "image/bmp" || fileContentType == "image/gif" ) 
			{

				string name = FileUpload1.PostedFile.FileName;                  // 客户端文件路径

				FileInfo file = new FileInfo( name );
				string fileName = file.Name;                                    // 文件名称
				String FileType = fileName.Substring( fileName.Length - 4, 4 );     //获的扩展名
				string photoName_New = DateTime.Now.Minute.ToString() + DateTime.Now.Second.ToString() + FileType;//用用户名和时间来重命名图片，以防重名  

				string webFilePath = Server.MapPath( "~/Upload/Flash/" + photoName_New );        // 服务器端文件路径

				if( !File.Exists( webFilePath ) )
				{
					try
					{
						FileUpload1.SaveAs( webFilePath );
						flashImg = "/Upload/Flash/" + photoName_New;
					}
					catch( Exception ex )
					{
						Response.Write( ex.Message );
						Response.End();
					}
				}
			}
			else
			{
				ClientScript.RegisterStartupScript( this.GetType(), "Login", "<script>alert('图片格式必须为jpg格式！')</script>" );
				return;
			}
		}
		#endregion

        string xmlpath = HttpContext.Current.Server.MapPath("/Upload/xml/flash.xml");

       XmlDocument xml=new XmlDocument();

       XmlElement xmlRoot;

       if (!File.Exists(xmlpath))
       {
             
           xml.LoadXml("<?xml version=\"1.0\" encoding=\"utf-8\"?><bcaster></bcaster>"); //.AppendChild(xmlRoot);   
           id = 0;
          
       }
       else {

           xml.Load(xmlpath);
           xmlRoot = xml.DocumentElement;
           XmlNodeList xnl = xmlRoot.GetElementsByTagName("item");
           foreach(XmlNode node in xnl)
           {
             int temp=Convert.ToInt32(node.Attributes["id"].Value);
             if (id < temp)
             {
                 id = temp;
             }
          
           }
           id = id + 1;

       
       }
          xmlRoot = xml.DocumentElement;
           XmlElement xmlSon = xml.CreateElement("item");
           XmlAttribute xmlAtt1 = xml.CreateAttribute("itemtitle");
           xmlAtt1.Value = title;
           xmlSon.Attributes.Append(xmlAtt1);

           XmlAttribute xmlAtt2 = xml.CreateAttribute("item_url");
           xmlAtt2.Value = flashImg;
           xmlSon.Attributes.Append(xmlAtt2);

           XmlAttribute xmlAtt3 = xml.CreateAttribute("link");
           xmlAtt3.Value = url;
           xmlSon.Attributes.Append(xmlAtt3);

           XmlAttribute xmlAtt4 = xml.CreateAttribute("id");
           xmlAtt4.Value = id.ToString();
           xmlSon.Attributes.Append(xmlAtt4);
           xmlRoot.AppendChild(xmlSon);
           try
           {
               xml.Save(xmlpath);
               CommonManager.Web.RegJs(this, "alert('操作成功！');location.href='flashad.aspx';", false);
           }
           catch (Exception ex)
           {
               CommonManager.Web.RegJs(this, "alert('操作失败！"+ex.Message+"');", false);
           }


	}
}
