# nm-otool
42 School's project: Recode nm and otool -t commands.
–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
```
$> ./ft_nm -h
usage: ./ft_nm [-nruUjth] [file ...]
```

*-n     Sort numerically rather than alphabetically.*<br/>
*-r     Sort in reverse order.*<br/>
*-u     Display only undefined symbols.*<br/>
*-U     Don't display undefined symbols*.<br/>
*-j     Just display the symbol names (no value or type).*<br/>
*-t     format*<br/>
- **d**      *The value shall be written in decimal.*<br/>
- **o**      *The value shall be written in octal.*<br/>
- **x**      *The value shall be written in hexadecimal (default).*<br/>

–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
<br/><br/>
`ft_otool` equivalent of `otool -t`<br/>
```
$> ./ft_otool -h
usage: ./ft_otool [file ...]
```
