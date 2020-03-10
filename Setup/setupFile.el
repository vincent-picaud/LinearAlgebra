(if my-project-root
    ;; Configuration
    (progn
      (message "Configuring %s " my-project-root)
      ;;
      ;; PDF Export config 
      ;;
      (setq org-image-actual-width (/ (display-pixel-width) 4))

      ;; uses the minted package instead of the listings one
      (setq org-latex-listings 'minted)
      
      ;; defines how to generate the pdf file using lualatex + biber
      (setq org-latex-pdf-process
      '("lualatex -shell-escape -interaction nonstopmode -output-directory %o %f"
      "biber %b"
      "lualatex -shell-escape -interaction nonstopmode -output-directory %o %f"
      "lualatex -shell-escape -interaction nonstopmode -output-directory %o %f"))
      ;;
      ;; Working Bibliography with HTML export requires ox-bibtex
      ;;
      (require 'ox-bibtex)
      ;;
      ;; Local bibliography
      ;;
      (setq my-bibtex-filename 
	    (concat my-project-root "Bibliography/bibliography.bib"))
      (if (file-exists-p my-bibtex-filename)
	  ;; If bibliography.bib exists 
	  (setq reftex-default-bibliography  `(,my-bibtex-filename)
	        bibtex-completion-notes-extension "-notes.org"
		bibtex-completion-notes-template-multiple-files "#+SETUPFILE: ../Setup/setupFile-1.org\n#+TITLE: ${author-or-editor} (${year}): ${title}\n\n* Personal Notes\n  :PROPERTIES:\n  :NOTER_DOCUMENT: ~/AnnotatedPDF/${=key=}.pdf\n  :END:\n\n[[file:~/AnnotatedPDF/${=key=}.pdf][${title}]]\n"

		bibtex-completion-bibliography my-bibtex-filename
		bibtex-completion-library-path (file-name-directory my-bibtex-filename)
		bibtex-completion-notes-path (file-name-directory my-bibtex-filename)
		
		org-ref-default-bibliography  `(,my-bibtex-filename)
		org-ref-pdf-directory (file-name-directory my-bibtex-filename)
	  )
	;; otherwise unbound meaningless my-bibtex-filename
	(makunbound 'my-bibtex-filename)
    )
      ;;
      ;; Agenda files
      ;;
      (setq org-agenda-files
	    (mapcar 'abbreviate-file-name
		    (split-string
		     (shell-command-to-string (format "find %s -name \"*.org\" ! -path \"./build/*\" ! -name \"index.org\"  ! -name \"agenda.org\"  ! -path \"./Setup/*\"" my-project-root))
		     "\n")))
      ;;
      ;; My my-workInProgress-filename and its associated captures
      ;;
      (setq my-www-links-filename (concat my-project-root "www_links.org"))
      (setq my-journal-filename (concat my-project-root "journal.org"))
      (setq my-todo-filename (concat my-project-root "todo.org"))

      (setq org-capture-templates
      	      `(
	      ;; Personal template (adapt them for your setting)
	      ;; ("A"
	      ;;  "Agenda/Meeting" entry (file+headline "~/GitLab/PVBibliography/agenda.org" "Agenda")
	      ;; "* %^{Title?} %^G\n:PROPERTIES:\n:Created: %U\n:END:\n\n %?"
	      ;; :empty-lines 1  
	      ;; :create t
	      ;; )
	      ;;
	      ;; ("K" "Log Time" entry (file+datetree "~/GitLab/PVBibliography/activity.org" "Activity")
	      ;; "* %U - %^{Activity}  :TIME:"
	      ;; )

		("t"
		 "Todo" entry (file+olp+datetree ,my-todo-filename)
		 "* TODO %^{Title?} [/] %^G\n:PROPERTIES:\n:Created: %U\n:END:\n\n - [ ] %?"
		 :empty-lines 1  
		 :create t
		)
		
		("T"
		 "Todo with file link" entry (file+olp+datetree ,my-todo-filename)
		 "* TODO %^{Title|%f} [/] %^G\n:PROPERTIES:\n:Created: %U\n:END:\n\nBack link: %a\n\n#+BEGIN_QUOTE\n%i\n#+END_QUOTE\n\n - [ ] %?"
		 :empty-lines 1  
		 :create t
		)
		
		("j" "Journal" entry (file+olp+datetree ,my-journal-filename)
		 "* %^{Title} %^G\n\n%?"
		 :empty-lines 1  
		 :create t
		)

		("J" 
		"Journal with file link" entry (file+olp+datetree ,my-journal-filename)
		 "* %^{Title|%f} %^G\n\nBack link: %a\n\n#+BEGIN_QUOTE\n%i\n#+END_QUOTE\n\n%?"
		 :empty-lines 1  
		 :create t
		)

		;;
		;; See: https://github.com/sprig/org-capture-extension for further details
		;;
		("L" 
		"Protocol Link" entry (file ,my-www-links-filename)
		"* [[%:link][%(transform-square-brackets-to-round-ones \"%:description\")]] \
		%^G\n:PROPERTIES:\n:Created: %U\n:END:\n\n%?"
		:empty-lines 1  
		:create t
		)
		
		("p" 
		"Protocol" entry (file ,my-www-links-filename)
		 "* [[%:link][%(transform-square-brackets-to-round-ones \"%:description\")]] \
		 %^G\n:PROPERTIES:\n:Created: %U\n:END:\n#+BEGIN_QUOTE\n%i\n#+END_QUOTE\n\n%?"
		 :empty-lines 1  
		 :create t
		)
		))
      ;;
      ;; You can publish in another place:
      ;;
      ;; (setq my-publish-dir "~/Temp/Publish")
      ;;
      ;; by default we publish in-place 
      ;; (advantage: C-c C-e h h directly update the published page)
      (setq my-publish-dir my-project-root)

      (setq my-project-name "LinearAlgebra")
   
      (defun my-org-publish-sitemap (title list)
	"Create my own index.org instead of the default one"
	(concat	"#+INCLUDE: \"index_preamble.org\"\n"
		"#+OPTIONS: toc:nil\n\n"
		"* Sitemap\n\n"
		(org-list-to-org list)
		"\n\n"))
  
      (setq org-publish-project-alist
	    `(
	      (,(concat my-project-name "_Org")
	       :base-directory ,my-project-root
	       :base-extension "org"
	       :recursive t
	       :publishing-directory ,my-publish-dir
	       :publishing-function org-html-publish-to-html
	       :sitemap-function my-org-publish-sitemap
	       :htmlize-source t
	       :org-html-head-include-default-style nil
	       :exclude "Setup*\\|index_preamble.org" 
	       ;; Generates theindex.org + inc files
	       :makeindex t
	       ;; Creates index.org, calls my-org-publish-sitemap to fill it
	       :auto-sitemap t
	       :sitemap-filename "index.org"
	      )

	      ;; (,(concat my-project-name "_Tangle")
	      ;;  :base-directory ,my-project-root
	      ;;  :base-extension "org"
	      ;;  :recursive t
	      ;;  :publishing-directory ,my-publish-dir
	      ;;  :publishing-function org-babel-tangle-publish
	      ;;  :exclude ".*bazel-.*"
	      ;;  )

	      (,(concat my-project-name "_Data")
	       :base-directory ,my-project-root
	       :base-extension "nb\\|?pp\\|png"
	       :recursive t
	       :publishing-directory ,my-publish-dir
	       :publishing-function org-publish-attachment
	       :exclude ".*bazel-.*"
	      )

	      ;; Main
	      (,my-project-name
	       :components (,(concat my-project-name "_Org")
	                    ;; ,(concat my-project-name "_Tangle")
			    ,(concat my-project-name "_Data"))
	      )
	      )
	)
      ) ; progn
  ;; else
  (error "Project root undefined")
    )
