using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using System.Data;
using Bzw.Data;
using System.IO;
using System.Xml;

 
    public partial class Admin_Lotter_PrEdit : AdminBasePage
    {
        string PrizesID;
        public string strName, strNum, strGoldRate, strSilverRate, strJadeRate, strPicName = "";
        protected void Page_Load(object sender, EventArgs e)
        {
            AdminPopedom.IsHoldModel("18");
            string tmp = CommonManager.Web.Request("id", "");
            if (string.IsNullOrEmpty(tmp) || !CommonManager.String.IsInteger(tmp))
            {
                Alert("请勿非法操作！", null);
                return;
            }
            else
                PrizesID = tmp;

            DataTable dt = DbSession.Default.FromSql("select * from Web_LotterAward where id=" + tmp).ToDataTable();
            if (dt.Rows.Count > 0)
            {
                strName = dt.Rows[0]["LotteryAwardName"].ToString();
                strNum = dt.Rows[0]["Number"].ToString();
                strGoldRate = dt.Rows[0]["GoldRate"].ToString();
                strSilverRate = dt.Rows[0]["SilverRate"].ToString();
                strJadeRate = dt.Rows[0]["JadeRate"].ToString();
                if (!string.IsNullOrEmpty(dt.Rows[0]["PicName"].ToString()) && dt.Rows[0]["PicName"].ToString().ToLower() != "/upload/prizes/nopic.jpg")
                {
                    phFileImage.Visible = false;
                    phImageUrl.Visible = true;
                    txtImageUrl.Text = dt.Rows[0]["PicName"].ToString();
                }
                else
                {
                    phImageUrl.Visible = false;
                    phFileImage.Visible = true;
                }
            }
            dt.Clear();
        }

        protected void Prizes_Edit(object sender, EventArgs e)
        {
            string sqlName, sqlNum, sqlGoldRate, sqlSilverRate, sqlJadeRate, sqlPicName = "";
            sqlName = CommonManager.Web.RequestForm("LotteryAwardName", "");
            if (strName == "")
            {
                Alert("温馨提示：\\n\\n奖品名称不能为空！", null);
                return;
            }
            sqlGoldRate = CommonManager.Web.RequestForm("GoldRate", "");
            if (!CommonManager.String.IsInteger(sqlGoldRate) || Convert.ToInt32(sqlGoldRate) < 0)
            {
                CommonManager.Web.RegJs(this, "alert('[金的概率]必须为不小于0的数字！');location.href=location.href;", false);
                return;
            }
            sqlSilverRate = CommonManager.Web.RequestForm("SilverRate", "");
            if (!CommonManager.String.IsInteger(sqlSilverRate) || Convert.ToInt32(sqlSilverRate) < 0)
            {
                CommonManager.Web.RegJs(this, "alert('[银的概率]必须为不小于0的数字！');location.href=location.href;", false);
                return;
            }
            sqlJadeRate = CommonManager.Web.RequestForm("JadeRate", "");
            if (!CommonManager.String.IsInteger(sqlSilverRate) || Convert.ToInt32(sqlSilverRate) < 0)
            {
                CommonManager.Web.RegJs(this, "alert('[玉的概率]必须为不小于0的数字！');location.href=location.href;", false);
                return;
            }
            sqlNum = CommonManager.Web.RequestForm("Num", "");
            if (!CommonManager.String.IsInteger(sqlNum) || Convert.ToInt32(sqlNum) < 0)
            {
                CommonManager.Web.RegJs(this, "alert('[奖品的数量]必须为不小于0的数字！');location.href=location.href;", false);
                return;
            }
            if (fuImage.HasFile)
            {
                try
                {
                    if (!CommonManager.File.UploadFile(fuImage.PostedFile, 300 * 1024, new string[] { "jpg", "jpeg", "gif" }, "/Upload/Lotter", FileOperator.RenameType.当前时间及随机数字, out sqlPicName))
                    {
                        sqlPicName = "/UpLoad/Prizes/NoPic.Jpg";
                    }
                }
                catch (Exception ex)
                {
                    CommonManager.Web.RegJs(this, "alert('文件上传错误：" + ex.Message + "');location.href=location.href;", false);
                    return;
                }
            }
            else
            { 
                  sqlPicName = txtImageUrl.Text.Trim();
            }

            string sql = @"UPDATE dbo.Web_LotterAward SET LotteryAwardName=@LotteryAwardName,GoldRate=@GoldRate,SilverRate=@SilverRate,JadeRate=@JadeRate,PicName=@PicName,Number=@Number WHERE id=@id ";
             int SqlState = DbSession.Default.FromSql(sql)
                .AddInputParameter("@LotteryAwardName", DbType.String, sqlName)
                .AddInputParameter("@GoldRate", DbType.String, sqlGoldRate)
                .AddInputParameter("@SilverRate", DbType.String, sqlSilverRate)
                .AddInputParameter("@JadeRate", DbType.String, sqlJadeRate)
                .AddInputParameter("@PicName", DbType.String, sqlPicName)
                .AddInputParameter("@Number", DbType.Int32, sqlNum)
                .AddInputParameter("@id", DbType.Int32, PrizesID)
                .Execute();
             if (SqlState > 0)
             {
                 string xmlPath = Server.MapPath("/Upload/xml/Lotter.xml");
                 if (!File.Exists(xmlPath))
                 {
                     return;

                 }

                 XmlDocument xml = new XmlDocument();
                 xml.Load(xmlPath);

                 string xp = "//item[@id='" + PrizesID + "']";

                 XmlElement xmlRoot = xml.DocumentElement;//取得文档的根节点
                 XmlNode xn = xmlRoot.SelectSingleNode(xp);


                 xn["name"].InnerText = sqlName;

                 xn["PicPath"].InnerText = sqlPicName;

                 xn["GoldRate"].InnerText = sqlGoldRate;

                 xn["SilverRate"].InnerText = sqlSilverRate;

                 xn["JadeRate"].InnerText = sqlJadeRate;
                 try
                 {
                     xml.Save(xmlPath);
                     CommonManager.Web.RegJs(this, "alert('修改成功！');location.href=location.href;", false);
                     
                 }
                 catch (Exception ex)
                 {
                     CommonManager.Web.RegJs(this, "alert('修改失败！" + ex.Message + "')", false);
                 }
             }
             else
             {
                 Alert("温馨提示：\\n\\n奖品资料修改失败！", null);
             }

        }
    }
 