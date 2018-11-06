

SDTSDLGHeader::SDTSDLGHeader(void)
{
   _resolution = 0;
   _horizDatum = 0;
   _grndRefSys = 0;
   _grndRefSysZone = 0;
}

SDTSDLGHeader::SDTSDLGHeader(CString& filename)
{
   // XXXJCF
   // Fun with opening lots and lots of files and playing with them.
}

SDTSDLGHeader::SDTSDLGHeader(const SDTSDLGHeader& header)
{
   _resolution = header._resolution;
   _horizDatum = header._horizDatum;
   _grndRefSys = header._grndRefSys;
   _grndRefSysZone = header._grndRefSysZone;
   for (int i = 0; i < 4; i++)
      {
         _controlPoints[i] = header._controlPoints[i];
      };
}
