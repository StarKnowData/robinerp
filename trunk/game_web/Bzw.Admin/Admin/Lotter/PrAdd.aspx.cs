using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using Bzw.Data;
using System.Data;
using System.IO;
using System.Xml;

 
    public partial class Admin_Lotter_PrAdd : AdminBasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            AdminPopedom.IsHoldModel("18");
        }

        protected void Prizes_Add(object sender, EventArgs e)
        {
            string strName, strNum, strGoldRate, strSilverRate, strJadeRate, strPicName="";
            strName = CommonManager.Web.RequestForm("LotteryAwardName", "");
            if (strName == "")
            {
                Alert("温馨提示：\\n\\n奖品名称不能为空！", null);
                return;
            }
            strGoldRate = CommonManager.Web.RequestForm("GoldRate", "");
            if (!CommonManager.String.IsInteger(strGoldRate) || Convert.ToInt32(strGoldRate) < 0)
            { 
                CommonManager.Web.RegJs(this, "alert('[金的概率]必须为不小于0的数字！');location.href=location.href;", false);
                return;
            }
            strSilverRate = CommonManager.Web.RequestForm("SilverRate", "");
            if (!CommonManager.String.IsInteger(strSilverRate) || Convert.ToInt32(strSilverRate) < 0)
            {
                CommonManager.Web.RegJs(this, "alert('[银的概率]必须为不小于0的数字！');location.href=location.href;", false);
                return;
            }
            strJadeRate = CommonManager.Web.RequestForm("JadeRate", "");
            if (!CommonManager.String.IsInteger(strSilverRate) || Convert.ToInt32(strSilverRate) < 0)
            {
                CommonManager.Web.RegJs(this, "alert('[玉的概率]必须为不小于0的数字！');location.href=location.href;", false);
                return;
            }
            strNum = CommonManager.Web.RequestForm("Num", "");
            if (!CommonManager.String.IsInteger(strNum) || Convert.ToInt32(strNum) < 0)
            {
                CommonManager.Web.RegJs(this, "alert('[奖品的数量]必须为不小于0的数字！');location.href=location.href;", false);
                return;
            }
            DataTable dt1 = DbSession.Default.FromSql("SELECT SUM(GoldRate) AS sumGold,SUM(SilverRate) AS sumSilver,SUM(JadeRate) AS sumJade FROM dbo.Web_LotterAward ").ToDataTable();

            if (dt1.Rows[0]["sumGold"].ToString() != "" && dt1.Rows[0]["sumSilver"].ToString() != "" && dt1.Rows[0]["sumJade"].ToString()!="")
            {
                int sgold = Convert.ToInt32(dt1.Rows[0]["sumGold"].ToString());
                int ssilver = Convert.ToInt32(dt1.Rows[0]["sumSilver"].ToString());
                int sjade = Convert.ToInt32(dt1.Rows[0]["sumJade"].ToString());
                if ((sgold + Convert.ToInt32(strGoldRate)) > 100)
                {
                    CommonManager.Web.RegJs(this, "alert('金的中奖总概率不能大于1！');location.href=location.href;", false);
                    return;
                }
                if ((ssilver + Convert.ToInt32(strSilverRate)) > 100)
                {
                    CommonManager.Web.RegJs(this, "alert('银的中奖总概率不能大于1！');location.href=location.href;", false);
                    return;
                }
                if ((sjade + Convert.ToInt32(strJadeRate)) > 100)
                {
                    CommonManager.Web.RegJs(this, "alert('玉的中奖总概率不能大于1！');location.href=location.href;", false);
                    return;
                }
            }
            if (fuImageUrl.HasFile)
            {
                try
                {
                    if (!CommonManager.File.UploadFile(fuImageUrl.PostedFile, 300 * 1024, new string[] { "jpg", "jpeg", "gif","png" }, "/Upload/Lotter", FileOperator.RenameType.当前时间及随机数字, out strPicName))
                    {
                        strPicName = "/UpLoad/Prizes/NoPic.Jpg";
                    }
                }
                catch (Exception ex)
                { 
                    CommonManager.Web.RegJs(this, "alert('文件上传错误：" + ex.Message + "');location.href=location.href;", false);
                    return;
                }
            }

            string sql = @"INSERT INTO [Web_LotterAward](
	[LotteryAwardName],[GoldRate],[SilverRate],[JadeRate],[PicName],[Number],[AddDate]
	)VALUES(
	@Name,@GoldRate,@SilverRate,@JadeRate,@PicName,@Number ,getdate())";
            int SqlState = DbSession.Default.FromSql(sql)
                .AddInputParameter("@Name", DbType.String, strName)
                .AddInputParameter("@GoldRate", DbType.Int32, strGoldRate)
                .AddInputParameter("@SilverRate", DbType.Int32, strSilverRate)
                .AddInputParameter("@JadeRate", DbType.Int32, strJadeRate)
                .AddInputParameter("@PicName", DbType.String, strPicName)
                .AddInputParameter("@Number", DbType.Int32, strNum) 
                .Execute();
            if (SqlState > 0)
            {
                string xmlPath = Server.MapPath("/Upload/xml/Lotter.xml");
                XmlDocument xml = new XmlDocument();
               
                if (!File.Exists(xmlPath))
                {
                    //如果不存在就创建该文件
                 
                    xml.LoadXml("<?xml version=\"1.0\" encoding=\"utf-8\"?><bcaster></bcaster>");//创建xml文件头部
                    XmlElement xmlRoot = xml.DocumentElement;//获取根元素
                    DataTable dt = DbSession.Default.FromSql("select * from Web_LotterAward").ToDataTable();
                    //遍历奖品
                    for (int i = 0; i < dt.Rows.Count; i++)
                    {
                        XmlElement xmlSon = xml.CreateElement("item");
                        XmlAttribute xmlattr = xml.CreateAttribute("id");
                        xmlattr.Value = dt.Rows[i]["id"].ToString();
                        xmlSon.Attributes.Append(xmlattr);

                        XmlAttribute xmlurl = xml.CreateAttribute("url");
                        xmlurl.Value = UiCommon.StringConfig.WebSiteName;
                        xmlSon.Attributes.Append(xmlurl);

                        XmlElement title = xml.CreateElement("name");
                        title.InnerText = dt.Rows[i]["LotteryAwardName"].ToString();
                        xmlSon.AppendChild(title);
                        XmlElement content = xml.CreateElement("PicPath");
                        content.InnerText = dt.Rows[i]["PicName"].ToString();
                        xmlSon.AppendChild(content);

                        XmlElement gold = xml.CreateElement("GoldRate");
                        gold.InnerText = dt.Rows[i]["GoldRate"].ToString();
                        xmlSon.AppendChild(gold);

                        XmlElement silver = xml.CreateElement("SilverRate");
                        silver.InnerText = dt.Rows[i]["SilverRate"].ToString();
                        xmlSon.AppendChild(silver);
                        XmlElement jade = xml.CreateElement("JadeRate");
                        jade.InnerText = dt.Rows[i]["JadeRate"].ToString();
                        xmlSon.AppendChild(jade);
                        XmlElement num = xml.CreateElement("Number");
                        num.InnerText = dt.Rows[i]["Number"].ToString();
                        xmlSon.AppendChild(num);
                        xmlRoot.AppendChild(xmlSon);
                    }
                    dt.Clear();
                    
                }
                else
                {
                    xml.Load(xmlPath);
                    DataTable dt = DbSession.Default.FromSql("select top 1 * from Web_LotterAward order by id desc").ToDataTable();
                    XmlElement xmlRoot = xml.DocumentElement;//获取根元素 
                    XmlElement xmlSon = xml.CreateElement("item");
                    XmlAttribute xmlattr = xml.CreateAttribute("id");
                    xmlattr.Value = dt.Rows[0]["id"].ToString();
                    xmlSon.Attributes.Append(xmlattr);

                    XmlAttribute xmlurl = xml.CreateAttribute("url");
                    xmlurl.Value = UiCommon.StringConfig.WebSiteName;
                    xmlSon.Attributes.Append(xmlurl);

                    XmlElement title = xml.CreateElement("name");
                    title.InnerText = dt.Rows[0]["LotteryAwardName"].ToString();
                    xmlSon.AppendChild(title);

                    XmlElement content = xml.CreateElement("PicPath");
                    content.InnerText = dt.Rows[0]["PicName"].ToString();
                    xmlSon.AppendChild(content);

                    XmlElement gold = xml.CreateElement("GoldRate");
                    gold.InnerText = dt.Rows[0]["GoldRate"].ToString();
                    xmlSon.AppendChild(gold);

                    XmlElement silver = xml.CreateElement("SilverRate");
                    silver.InnerText = dt.Rows[0]["SilverRate"].ToString();
                    xmlSon.AppendChild(silver);

                    XmlElement jade = xml.CreateElement("JadeRate");
                    jade.InnerText = dt.Rows[0]["JadeRate"].ToString();
                    xmlSon.AppendChild(jade);

                    XmlElement num = xml.CreateElement("Number");
                    num.InnerText = dt.Rows[0]["Number"].ToString();
                    xmlSon.AppendChild(num);

                    xmlRoot.AppendChild(xmlSon);
                    dt.Clear();
                 
                }
                try
                {
                    xml.Save(xmlPath);
                    CommonManager.Web.RegJs(this, "alert('操作成功！');location.href='Pradd.aspx';", false);
                }
                catch (Exception ex)
                {
                    CommonManager.Web.RegJs(this, "alert('操作失败！" + ex.Message + "');", false);
                }
            }
        }
    }
 
