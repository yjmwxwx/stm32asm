;;; forthblocks.el -- edit Forth-style blocks within a text file
;;; Copyright 2008 by Frank Sergeant <frank@pygmy.utoh.org>

;;; forthblocks mode is free software distributed under the terms
;;; of the GNU General Public License, version 2.  For details,
;;; see the file gpl-2.0.txt.

;;; This is version 0.1 of 8 October 2008.

;;; For more information about forthblocks mode, see 
;;; http://pygmy.utoh.org.


;;; This mode is derived now from text-mode.  Later, I wonder if I should derive 
;;; from comint-mode or some such, to make it easier to move to the Forth
;;; interactive window and to send Forth snippets to be executed.

;;; See the comment below in the definition of forthblocks-mode or, start
;;; forthblocks mode with
;;;    M-x forthblocks-mode
;;;
;;; then press 
;;;    C-h m

;;; To do:
;;;    open a Forth process and communicate with it using comint.

(require 'comint)
(require 'derived)

(define-derived-mode forthblocks-mode text-mode "forthblocks"
  "Major mode for editing Forth block files within a text file.
Special commands:
\\{forthblocks-mode-map}

This mode helps you edit a text file (almost) as if it were a
traditional Forth block file.  The trick is to mark the beginning
of each logical block with a special comment.  The left
parenthesis must start at the begininng of a line, be followed by
a single space, followed by either the word 'block' or the word
'shadow', followed by at least one space.  Of course, since this
is a Forth comment, it should end eventually on the same line
with a closing right parenthesis.

Here are some examples:

( block 1   ------------------  load block)
( shadow 1 )
( block 2  miscellaneous)
( shadow 2 miscellaneous )

The blocks numbers do not need to be consecutive, but they should
be monotonically increasing.  Shadow blocks are not essential but,
if they are used, should follow their associated source blocks.

Put this file (forthblocks.el) somewhere in your load path or put
the full path to forthblocks.el in the autoload form shown below.

Put something like the following in your .emacs file so that files 
ending in in .fth will be opened in forthblocks mode.  The following
example assumes forthblocks.el is in your home directory.

(setq auto-mode-alist
      (cons '(\"\\.fth\" . forthblocks-mode) auto-mode-alist))
(autoload 'forthblocks-mode \"~/forthblocks.el\" \"Forth blocks editing mode.\" t)

The available commands are:

M-< (goto-first-block) and M-> (goto-last-block) 
   move to the first and last blocks, staying on the same type of
   block (source or shadow).

C-v (forward-block-narrow) and M-v (backward-block-narrow) 
(or the page-up and page-down keys) 
   move forward or backward a single block (or more, with a prefix
   number), but staying on the same type of block.  If you are on
   a source block, then C-v moves to the following source block.
   If you are on a shadow block, then C-v moves to the following
   shadow block.

M-a (alternate-block) 
   switches from a source block to its associated
   shadow block or vice versa.

renumber-blocks 
   renumber the blocks consecutively, starting with the block
   number of the first block in the file.

C-x n w
   widen the file (so all blocks are visible at once)
"
  (make-local-variable 'page-delimiter)
  ;(make-local-variable 'paragraph-separate)
  ;(make-local-variable 'paragraph-start)
  (setq page-delimiter "^( \\(block\\|shadow\\) ")
  (setq any-block-regexp page-delimiter)
  (setq source-block-regexp   "^( block ")
  (setq shadow-block-regexp  "^( shadow ")
  ;(setq fill-column 63)
  (setq fill-column 72)
  ;(make-local-variable 'block-mode)
  ;(setq block-mode 'source)
  ;(setq paragraph-start page-delimiter)
  ;(setq paragraph-start page-delimiter)

)

(define-key forthblocks-mode-map "\C-v" 'forward-block-narrow)
(define-key forthblocks-mode-map "\M-v" 'backward-block-narrow)
(define-key forthblocks-mode-map [next] 'forward-block-narrow)
(define-key forthblocks-mode-map [prior]  'backward-block-narrow)
(define-key forthblocks-mode-map "\M-<" 'goto-first-block)
(define-key forthblocks-mode-map "\M->" 'goto-last-block)
(define-key forthblocks-mode-map "\M-a" 'alternate-block)

; Note, I am using M-a for alternate-block.  Normally, M-a is bound to
; backward-sentence.  Feel free to change this.

(defun start-of-block-p () 
  "Answer whether point is at the start of a block marker."
  (interactive)
  (looking-at any-block-regexp))

(defun start-of-shadow-block-p () 
  "Answer whether point is at the start of a shadow block."
  (interactive)
  (looking-at shadow-block-regexp))

(defun start-of-source-block-p () 
  "Answer whether point is at the start of a source block."
  (interactive)
  (looking-at source-block-regexp))

(defun current-block-type () 
  "Answer 'block or 'shadow or nil, depending on type of current block."
  (interactive)
  (save-excursion
    (beginning-of-block)
    (if (start-of-shadow-block-p)
        'shadow
        'source)))

(defun show-block-type ()
  (interactive)
  (message "current block type is %s" (current-block-type)))

(defun current-block-number ()
  "Answer the block number of the current block.  
   This is taken from the block header, so it is a 'logical' block number
   rather than a count of physical blocks."
   (interactive)
   (save-excursion
     (beginning-of-block)
      (when (start-of-block-p)
           (progn
             (re-search-forward "^( \\(block\\|shadow\\) \\([[:digit:]]+\\)")
             (string-to-number (match-string-no-properties 2))))))

(defun what-block ()
  "Display the block number of the current block.  
   This is taken from the block header, so it is a 'logical' block number
   rather than a count of physical blocks."
   (interactive)
   (message "You are on block number %s of a %s block"
            (current-block-number) 
            (current-block-type)))

(defun forward-block-1 (&optional arg blktype)
  "Move forward to beginning of next block.  With ARG, move forward multiple blocks.
   With negative ARG, move backward to start of previous block.  If blktype is nil,
   go to the next block regardless of its type.  Otherwise, accept only the blocks
   of the requested BLKTYPE (i.e., 'source or 'shadow).  Leave point positioned at
   the beginning of the block.  When there do not exist enough occurrences to satisfy
   ARG (i.e. the COUNT), the go to end of buffer and search backward for first block
   of the requested type.  Caller must already have widened the buffer."
  (interactive "p")
  (or arg (setq arg 1))
  (message "starting to run #'forward-block-1")
  (let (goal)
    (setq goal (if blktype
                 (if (eq blktype 'source)
                     source-block-regexp
                     shadow-block-regexp)
                 any-block-regexp))
    (message (concat "The goal is " goal))
    (if (minusp arg)
        (progn
          (setq arg (abs arg))
          (beginning-of-block)
          (unless (re-search-backward goal nil t arg)
            ;; There were not enough occurrences, so we have not yet moved POINT.
            ;; Move to the beginning of the buffer, then go forward to the block type we
            ;; are looking for.
            (goto-char (point-min))
            (re-search-forward goal nil t 1)))
        (progn
          (end-of-line)   ; in case we are already at the start of a block
          (unless (re-search-forward goal nil t arg)
            ;; There were not enough occurrences, so we have not yet moved POINT.
            ;; Move to the end of the buffer, then back up to the block type we
            ;; are looking for.
            (goto-char (point-max))
            (re-search-backward goal nil t 1))))
    (beginning-of-block)))

(defun backward-block-1 (&optional arg blktype)
  "Move backward to beginning of next block.  See forward-block-1."
  (interactive "p")
  (or arg (setq arg 1))
  (forward-block-1 (- arg) blktype))

(defun beginning-of-block ()
  "Move to the beginning of the current block"
  (interactive)
  (end-of-line)   ; move out of block marker if we are in one
  (re-search-backward any-block-regexp nil 'end))

(defun end-of-block ()
  "Move to the end of the current block"
  (interactive)
  (end-of-line)   ; move out of block marker if we are in one
  (re-search-forward any-block-regexp nil 'end)
  (beginning-of-line)
  (when (start-of-block-p)
    (forward-line -1)
    (end-of-line)))

(defun forward-block-narrow (&optional arg)
  "Move forward to start of next block of the same type and narrow the region 
   to that block.  If ARG, move forward multiple blocks.  If ARG is negative, 
   move backwards and narrow."
  (interactive "p")
  (or arg (setq arg 1))
  (let (start (block-type (current-block-type)))
    (beginning-of-block)
    (setq start (point)) ; in case there is no following/preceding block
    (widen)
    (if (minusp arg)
        (progn
          (setq arg (abs arg))
          (backward-block-1 arg block-type))
        (forward-block-1 arg block-type))
    (beginning-of-block)
    (setq start (point))
    (end-of-block)
    (unless (eobp)
      (forward-char 1))
    (narrow-to-region start (point))
    (goto-char (point-min))))

(defun backward-block-narrow (&optional arg)
  "Move backward to start of previous block and narrow the region to that block.
   If ARG, move backward multiple blocks.  See forward-block-narrow."
  (interactive "p")
  (or arg (setq arg 1))
  (forward-block-narrow (- arg)))

(defun alternate-block ()
  "If we are on a source block, move forward to the associated shadow block.  
   If we are on a shadow block, move backward to the associated source block.
   If we do not find the type of block we are looking for, create it."
  (interactive)
  (let ((blktype (current-block-type))
        (blknum (current-block-number)))
    (widen)
    (message (format "alternate-block:  blktype is %s, blknum is %s" blktype blknum))
    (if (eq blktype 'source)
        (progn
          ;; go forward to the next block which should be a shadow block
          (message "alternate-block:  about to run forward-block-1")
          (forward-block-1)
          (when (start-of-source-block-p)
            ;; utoh, we were looking for a shadow block but the next block
            ;; was *not* a shadow block.  So, create one.
            (forward-line -1)
            (end-of-line)
            (insert (format "\n( shadow %d   inserted automatically)\n" blknum))))
          ;; else, go backward to the previous block, which should be a source block
          (backward-block-1))
    (block-narrow)))


(defun goto-first-block ()
  "Move to the first block and narrow it."
  (interactive)
  (widen)
  (goto-char (point-min))
  (backward-block-narrow))

(defun goto-last-block ()
  "Move to the last block and narrow it."
  (interactive)
  (widen)
  (goto-char (point-max))
  (beginning-of-block)
  (when (start-of-shadow-block-p)
    (backward-block-1))
  (block-narrow))

(defun block-narrow ()
  "Narrow the current block"
  (interactive)
  (beginning-of-block)
  (let ((start (point)))
    (end-of-block)
    (message (format "block-narrow:  about to narrow from %s to %s" start (point)))
    (narrow-to-region start (point))
    (goto-char (point-min))))

(defun renumber-blocks ()
  "Run through the current buffer, renumbering the blocks sequentially.
   Start with the number in the first block."
  (interactive)
  (save-excursion
    (save-restriction
      (widen)
      (goto-char (point-min))
      (let (old-num (new-num (current-block-number)))
        (end-of-line)
        (while (re-search-forward "^( \\(block\\|shadow\\) \\([[:digit:]]+\\)" nil t)
          (message "%s %s" (match-string 1) (match-string 2))
          (save-match-data
            (beginning-of-line)
            (when (start-of-source-block-p)
              (message "At start of a source block.  Before bumping, new-num is %d" new-num)
              (setq new-num (1+ new-num))) ; only bump new-num for a new source block
            (setq old-num (current-block-number)))
          (message "About to set old-num %d to new-num %d" old-num new-num)
          (unless (eq old-num new-num)
            (replace-match (number-to-string new-num) t t nil 2))
          (end-of-line))))))
        

(provide 'forthblocks)

;;; forthblocks.el ends here
