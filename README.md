# History of Fortune

This repository captures and reconstructs the historical revisions of the [fortune](https://en.wikipedia.org/wiki/Fortune_%28Unix%29) command, all the way from the initial 1979 implementation in [UNIX/32V](https://en.wikipedia.org/wiki/UNIX/32V) to Pascal Hakim's v1.99.1 that most modern versions (including <https://github.com/shlomif/fortune-mod>) are derived from.

Look at the git history to see -- many of my commits contain notes about reconstruction, including omissions/etc.

## Remaining Work

- Importing debian versions after 1.99.1-1 (current is 1.99.1-7.3), see <https://tracker.debian.org/pkg/fortune-mod>.
- Fixing up time/author/etc of commits.
- Other branches of fortune e.g. FreeBSD.
- How 1.99.1 pulls in changes from Debian.
  I don't think there's enough publicly available information for this, other than maybe by digging through the CVS history in <https://alioth-archive.debian.org/cvs/fortune.tar.xz>.
- Debian revisions before 9708-27. -26 is in that CVS repo but is kinda unclear due to it gradually importing from both -25 and -26.
- I don't think these exist anymore, but revisions of Amy's versions corresponding to changes in `Changelog`.

## Sources

- BSD source code from The Unix Heritage Society <https://minnie.tuhs.org/cgi-bin/utree.pl>, plus information about the history of BSD from <https://en.wikipedia.org/wiki/History_of_the_Berkeley_Software_Distribution> and <https://gunkies.org/wiki/Main_Page>.
- 4.4BSD-Lite from <http://http.pl.scene.org/pub/unix/systems/BSD/4.4BSD-Lite/>.
- 368BSD from <https://github.com/386bsd/386bsd>.
- Florian La Roche's version from <https://ftp.funet.fi/pub/linux/util/games/> (and I think also <https://www.ibiblio.org/pub/historic-linux/ftp-archives/sunsite.unc.edu/Sep-29-1996/games/>).
- Amy A. Lewis's version from <https://www.ibiblio.org/pub/historic-linux/ftp-archives/sunsite.unc.edu/Sep-29-1996/games>.
- Dennis L. Clark's version from <https://web.archive.org/web/19990506115004/http://www.progsoc.uts.edu.au/~dbugger/hacks/hacks.html>.
- Pascal Hakim's version from <https://web.archive.org/web/20070829015625/http://www.redellipse.net/code/fortune>.
- Historical Debian sources are from <https://snapshot.debian.org/package/fortune-mod/>, with more detail from <https://alioth-archive.debian.org/cvs/fortune.tar.xz>.
