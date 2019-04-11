
; for f in FILES ; do emacs-nox -batch -l upd-copyright.el; done
;; doesn't work...

(require 'copyright)
(copyright-update)
(save-buffer)
